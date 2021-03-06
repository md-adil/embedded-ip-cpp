#ifndef EVENTS_HANDLER_H
#define EVENTS_HANDLER_H
#include <iostream>
#include <string>
#include "../util/json.h"

class EventHandler {
public:
    virtual void handle() {}
    virtual void handle(std::string) {};
};

class EmptyEventHandler: EventHandler {
public:
    typedef void (*Callback)();
    EmptyEventHandler(Callback);
    void handle();
private:
    Callback callback;
};


class StringEventHandler: EventHandler {
public:
    typedef void (*Callback)(std::string);
    StringEventHandler(Callback);
    void handle(std::string);
private:
    Callback callback;
};

class JSONEventHandler: EventHandler {
public:
    typedef void (*Callback)(JSON);
    JSONEventHandler(Callback);
    void handle(std::string);
private:
    Callback callback;
};
#endif
