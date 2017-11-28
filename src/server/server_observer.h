#include <string>
#include "../actions/action.hpp"

#ifndef server_observer_h
#define server_observer_h

// An abstract class that is subclassed to allow messages (Actions) recieved
// by a Server to be used.
class ServerObserverInterface {
public:
    virtual ~ServerObserverInterface() {}
    virtual void notify(Action *action) = 0;
};

#endif // server_observer_h
