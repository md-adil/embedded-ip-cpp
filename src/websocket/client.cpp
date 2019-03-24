#include <iostream>
#include "client.h"

WebsocketClient::WebsocketClient() {
    std::cout << "Intialin" << std::endl;
}

WebsocketClient::~WebsocketClient() {
    delete _url;
}

WebsocketClient::WebsocketClient(string url) {
    _url = new URL(url);
}

WebsocketClient::WebsocketClient(URL url) {
    _url = &url;
}

void WebsocketClient::sendHeader() {
    const string NL = "\r\n";
    _key = base64_encode(_random.string(16));
    string handshake = "GET ";
    handshake += _url->uri + " HTTP/1.1" + NL;
    handshake += (string)"Host: " + _url->host + ":" + to_string(_url->port) + NL;
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
        return errno;
    }
    sockaddr_in address;
    sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_url->port);
    serv_addr.sin_addr.s_addr = inet_addr(_url->host.c_str());
    status = ::connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (status < 0) { 
        return errno;
    }
    sendHeader();
    return 0;
}

void WebsocketClient::readHeader() {
    ::recv(sock, (void *)_headers, 512, _FLAG);
    char headerBody[256];
    ::recv(sock, (void *)headerBody, 256, _FLAG);
}

int WebsocketClient::read() {
    char buf[buf_len];
    cout << "Receving" << endl;
    ssize_t recv_len = recv(sock, buf, buf_len, _FLAG);
    std::cout << "reading: " << (string)buf << endl;
    if(recv_len < 0) {
        return errno;
    }
    if(recv_len == 0) {
        return 0;
    }
    for(int i = 0; i < recv_len; i++) {
        cout << (int)buf[i] << ",";
    }
    cout << endl;

    // Check if connected;
    if(buf == "40") {
        _isConnected = true;
    }
    // Check for ping request
    if(buf == "0") {
        // Got pong
    }
    return recv_len;
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