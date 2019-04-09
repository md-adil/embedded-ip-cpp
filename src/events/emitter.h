#ifndef EVENTS_EMITTER_H
#define EVENTS_EMITTER_H
#include <string>
#include <vector>
#include <map>
#include "handler.h"
#include "../util/json.h"

using namespace std;

class EventEmitter {
public:

    typedef void (*StringHandler)(string data);
    typedef void (*JSONHandler)(JSON *);
    typedef void (*EmptyHandler)();
    ~EventEmitter();
    void on(string, EventHandler *);
    void on(string, StringHandler);
    void on(string, JSONHandler);
    void on(string, EmptyHandler);
    void emit(string, string);
    void dispatch(string, string);
    void dispatch(string);
protected:
    virtual void _send(string){}
private:
    map<string, vector<EventHandler*>> _eventHandlers;
};

#endif
