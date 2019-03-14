#include "emitter.h"

void EventEmitter::emit(string key, string data) {

}

void EventEmitter::on(string key, EventHandler * handler) {
    if(_eventHandlers.count(key) == 0) {
        vector<EventHandler *> emptyHandlers;
        _eventHandlers[key] = emptyHandlers;
    }
    _eventHandlers.at(key).push_back(handler);
}

void EventEmitter::on(string key, StringHandler _handler) {
    StringEventHandler * handler = new StringEventHandler(_handler);
    return on(key, (EventHandler*)handler);
}

void EventEmitter::on(string key, EmptyHandler _handler) {
    return on(key, (EventHandler*)new EmptyEventHandler(_handler));
}


void EventEmitter::on(string key, JSONHandler handler) {
    return on(key, (EventHandler*)new JSONEventHandler(handler));
}

void EventEmitter::dispatch(string key, string data) {
    if(_eventHandlers.count(key) == 0) return;
    for(auto it : _eventHandlers.at(key)) {
        it->handle(data);
    }
}
