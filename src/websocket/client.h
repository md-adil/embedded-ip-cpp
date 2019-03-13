#ifndef WEBSOCKET_H
#define WEBSOCKET_H
#include <string>
#include <iostream>
#include "../util/url.h"
#include "../events/emitter.h"

using namespace std;

class WebsocketClient: EventEmitter {
public:
    WebsocketClient();
    WebsocketClient(string);
    WebsocketClient(URL);
    int connect(string);
    int disconect();
    int send();
    int recv();

private:
    URL * url;
};

#endif
