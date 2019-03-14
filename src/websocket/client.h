#ifndef WEBSOCKET_H
#define WEBSOCKET_H
#include <string>
#include <iostream>
#include "../util/url.h"
#include "../events/emitter.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <map>
#include <cjson/cJSON.h>

using namespace std;

#define PORT 3040
// 0{"sid":"bBLi8NR4ZvUDwyNIAAAA","upgrades":[],"pingInterval":25000,"pingTimeout":5000}
class WebsocketClient: public EventEmitter {

public:
    int ping();
    int pingInterval = 25000;
    enum Type_t {
        ADD_CONVERT_ERROR,
        CONNECT_ERROR,
        READ_EMPTY,
        READ,
        SEND_ERROR,
        SENT
    };

    WebsocketClient();
    WebsocketClient(string);
    WebsocketClient(URL);
    int connect();
    int disconect();
    int send();
    int read();

private:
    const int _FLAG = 0;
    int sock = 0;
    size_t buf_len = 256;
    bool _isConnected = false;
    void sendHeader();
    // Client specific address
    URL * _url;
    string _sessionId;
    string _key;
};

#endif
