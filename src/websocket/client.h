#ifndef WEBSOCKET_H
#define WEBSOCKET_H
#include <string>
#include <iostream>
#include "../util/url.h"
#include "../util/random.h"
#include "../util/base64.h"
#include "../events/emitter.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <string.h> 
#include <arpa/inet.h>

using namespace std;
// 0{"sid":"bBLi8NR4ZvUDwyNIAAAA","upgrades":[],"pingInterval":25000,"pingTimeout":5000}
class WebsocketClient: public EventEmitter {

public:
    enum Type_t {
        SUCCESS,
        ERROR,
        SENT,
        READ,
        SEND_ERROR,
        READ_EMPTY,
        CONNECT_ERROR,
        ADD_CONVERT_ERROR,
        BUFFER_OVERFLOW
    };

    enum OPCode {
        CONTINUE=0x0,
        TEXT=0x1,
        BIN=0x2,
        CLOSE=0x8,
        PING=0x9,
        PONG=0xa
    };

    struct Frame {
        bool fin = 1;
        bool rsv1 = 0;
        bool rsv2 = 0;
        bool rsv3 = 0;
        bool hasMask = 1;
        uint8_t maskKey[4] = {0x00, 0x00, 0x00, 0x0};
        int size;
        OPCode code = TEXT;
    };

    WebsocketClient();
    ~WebsocketClient();
    WebsocketClient(string);
    WebsocketClient(URL);
    int ping();
    int connect();
    int disconect();
    int read();
    Type_t sendFrame(Frame, const char *);
    void emit(string event, JSON & json);
    void emit(string event, string string);

protected:
    Type_t withType(int);

private:
    const int _FLAG = 0;
    const string _version = "13";
    int sock = 0;
    size_t buf_len = 256;
    bool _isConnected = false;
    bool _isHeader = false;
    int _pingInterval = 25000;
    int _pingIntervalTimeout = 5000;
    string _sessionId;
    string _key;
    URL * _url;
    Random _random;
    void sendHeader();
    char * _headers;
    void readHeader();
};

#endif
