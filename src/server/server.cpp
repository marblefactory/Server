#include "server.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../../libs/json.hpp"
#include "../json/action_parser.hpp"

using std::cout;
using std::endl;
using nlohmann::json;
using json_parsing::parse_action;

// Create a server listening on the specified port for connections, for
// IP version 4.
Server::Server(boost::asio::io_service &io_service, int port):
    io_service(io_service),
    acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
    client_socket(io_service),
    is_client_connected(false)
{
}

// Listen for a connection from a single client. Then listens to messages from
// the client until it disconnects, at which point it waits for another client.
void Server::accept_client() throw(boost::system::system_error) {
    while (true) {
        acceptor.accept(client_socket);

        cout << "Client connected" << endl;

        is_client_connected = true;
        listen_to_client();
    }
}

// Listens to messages from the connected client, until the client disconnects.
void Server::listen_to_client() throw(boost::system::system_error) {
    while (is_client_connected) {
        // Recieve a message from the client.
        boost::array<char, MAX_BUFFER_SIZE> buf;
        boost::system::error_code error;

        size_t len = client_socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof) {
            cout << "Client Socket Closed" << endl;

            // Connection closed cleanly by peer.
            is_client_connected = false;
            client_socket.close();
            break;
        }
        else if (error) {
            // Some other error.
            throw boost::system::system_error(error);
        }
        else {
            // Use the recieved message.
            string str(buf.begin(), len);

            // The full message may contain multiple messages as they become combined since
            // we are using TCP. This splits the messages on the '$' delimiter and returns
            // all the messages.
            vector<string> messages;
            split(messages, str, boost::is_any_of("$"));

            vector<Action*> actions = parse_messages(messages);
            notify_observers(actions);
        }
    }
}

// Parses the string message recieved into actions.
vector<Action*> Server::parse_messages(vector<string> messages) {
    vector<Action*> actions;

    for (auto &message: messages) {
        cout << "JSON: " << message << endl;
        json j = json::parse(message);
        Action *action = parse_action(j);
        actions.push_back(action);
    }

    return actions;
}

// Adds an observer. This recieves a notification from the server when
// a parsed JSON message is recieved.
void Server::add_observer(ServerObserverInterface *observer) {
    observers.push_back(observer);
}

// Notifies all observers of the recieved actions.
void Server::notify_observers(vector<Action*> actions) {
    for (auto *action: actions) {
        for (ServerObserverInterface *observer: observers) {
            observer->notify(action);
        }
    }
}
