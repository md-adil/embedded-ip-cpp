#include "handler.h"

void EventHandler::handle(std::string data) { }

StringEventHandler::StringEventHandler(Callback _cb) {
    callback = _cb;
}

void StringEventHandler::handle(string _data) {
    callback(_data);
}

JSONEventHandler::JSONEventHandler(Callback _cb) {
    callback = _cb;
}

void JSONEventHandler::handle(string _data) {
    JSON * json = new JSON(_data);
    callback(json);
}
