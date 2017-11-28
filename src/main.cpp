#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include "server/server.h"
#include "server/server_observer.h"
#include "actions/action.hpp"

using boost::asio::ip::tcp;
using namespace std;

// A simple server observer which prints out the action recieved.
class TestObserver: public ServerObserverInterface {
    void notify(Action *action) {
        Move *move = (Move*)action;
        cout << move->dest << endl;
    }
};

int main() {
    try {
        TestObserver obs;

        boost::asio::io_service io_service;
        Server server(io_service, 1024);
        server.add_observer(&obs);

        server.accept_client();
    }
    catch (std::exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
