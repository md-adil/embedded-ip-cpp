#include <iostream>
#include <unistd.h>
#include "client.h"

WebsocketClient::~WebsocketClient() {
}
WebsocketClient::WebsocketClient(URL url): _url(url) {
    // connect();
}

void WebsocketClient::sendHeader() {
    const string NL = "\r\n";
    _key = base64_encode(_random.string(16));
    string handshake = "GET ";
    handshake += _url.uri + " HTTP/1.1" + NL;
    handshake += (string)"Host: " + _url.host + ":" + to_string(_url.port) + NL;
    handshake += "Connection: Upgrade" + NL;
    handshake += "Upgrade: websocket" + NL;
    handshake += "Sec-WebSocket-Version: " + _version + NL;
    handshake += "Sec-WebSocket-Key: " + _key + NL;
    handshake += "User-Agent: Websocket-Client" + NL;
    handshake += NL; // trigger
    ::send(sock, (uint8_t*)handshake.c_str(), handshake.size(), _FLAG);
    readHeader();
}

int WebsocketClient::connect() {
    int status;
    sock = socket(AF_INET, SOCK_STREAM, _FLAG);
    if (sock < 0) {
        dispatch("error", "Unable to initialize socket");
        return errno;
    }
    sockaddr_in address;
    sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_url.port);
    serv_addr.sin_addr.s_addr = inet_addr(_url.host.c_str());
    status = ::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (status < 0) {
        dispatch("error", "Unable to connect");
        return errno;
    }
    _isConnected = true;
    sendHeader();
    return 0;
}

void WebsocketClient::readHeader() {
    ::recv(sock, (void *)_headers, 512, _FLAG);
    char headerBody[256];
    ::recv(sock, (void *)headerBody, 256, _FLAG);
    cout << headerBody << endl;
}

int WebsocketClient::read() {
    uint8_t head[8];
    int len = 0, size;
    size = recv(sock, (void*)head, 2, MSG_DONTWAIT);
    if(size == -1) {
        return size;
    }

    if(size == 0) {
        _isConnected = false;
        return size;
    }

    len = (int)head[1];
    if(len >= 126) {
        recv(sock, (void*)head, 2, MSG_DONTWAIT);
        len = int((head[0]<<8)|(head[1])&0xff);
    }

    if(len < 1) {
        return 0;
    }

    char payload[len + 1];
    recv(sock, (void*)payload, len, MSG_DONTWAIT);
    payload[len] = '\0';
    string message = payload;
    if(message.find("0") == 0) {
        JSON ping = JSON::parse(message.substr(1, message.size()));
        _pingInterval = ping.get("pingInterval").toNumber() / 1000;
        _pingTimeout = ping.get("pingTimeout").toNumber() / 1000;
        return 0;
    }

    if(message.find("40") == 0) {
        dispatch("connect");
        return 0;
    }

    if(message.find("42") == 0) {
        vector<JSON> data = JSON::parse(message.substr(2, message.size())).toArray();
        if(data[1].isString()) {
            dispatch(data[0].toString(), data[1].toString());
        } else {
            dispatch(data[0].toString(), data[1].json());
        }
    }

    return 0;
}

int WebsocketClient::ping() {
    Frame frame;
    frame.size = 1;
    sendFrame(frame, "2");
    return 0;
}

WebsocketClient::Type_t WebsocketClient::sendFrame(Frame frame, const char * payload) {
    cout << payload << endl;
    int headerLen = frame.size + 4;
    uint8_t * header = new uint8_t[frame.size + 10];
    uint8_t * copy = header;
    *header = 0x00;
    *header |= frame.fin << 7;
    *header |= frame.code;
    header++;
    *header = 0x00;
    *header |= frame.hasMask << 7;
    if(frame.size < 126) {
        *header |= frame.size;
        headerLen += 2;
    } else if (frame.size < 0xFFFF) {
        *header |= 126;
        header++;
        *header = (frame.size>>8)&0xFF;
        header++;
        *header = (frame.size)&0xFF;
        header++;
        headerLen += 4;
    } else {
        return BUFFER_OVERFLOW;
    }
    memcpy(++header, frame.maskKey, 4);
    memcpy(header + 4, payload, frame.size);
    header = copy;
    ::send(sock, (void*)header, headerLen, _FLAG);
    delete [] header;
    return SUCCESS;
}

void WebsocketClient::emit(string evt, string message) {
    Frame frame;
    string payload = (string)"42[\"" + evt + "\",\"" + message + "\"]";
    frame.size = payload.size();
    sendFrame(frame, payload.c_str());
}

void WebsocketClient::emit(string evt, JSON & json) {
    Frame frame;
    string payload = (string)"42[\"" + evt + "\"," + json.json() + "]";
    frame.size = payload.size();
    sendFrame(frame, payload.c_str());
}

void WebsocketClient::loop() {
    time_t startAt = time(NULL);
    while(true) {
        if(!_isConnected) {
            connect();
        }

        time_t currentTime = time(NULL);
        if(_pingInterval && currentTime - startAt > _pingInterval) {
            startAt = currentTime;
            ping();
        }
        read();
        sleep(1);
    }
}

void WebsocketClient::operator()() {
   
}