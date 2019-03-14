#include <iostream>
#include "client.h"

WebsocketClient::WebsocketClient() {
    std::cout << "Intialin" << std::endl;
}

WebsocketClient::WebsocketClient(string url) {
    _url = new URL(url);
}

WebsocketClient::WebsocketClient(URL url) {
    _url = &url;
}

void WebsocketClient::sendHeader() {
    const string NL = "\r\n";
    _key = "MTIzMTI0NTYyMzU0NzY5OA==";

    string handshake = "GET ";
    handshake += _url->uri + " HTTP/1.1" + NL;
    handshake += (string)"Host: " + _url->host + ":" + to_string(_url->port) + NL;
    handshake += "Connection: Upgrade" + NL;
    handshake += "Upgrade: websocket" + NL;
    handshake += "Sec-WebSocket-Version: 13" + NL;
    handshake += "Sec-WebSocket-Key: " + _key + NL;
    handshake += "User-Agent: Websocket-Client" + NL;
    handshake += NL; // trigger
    int sentcode = ::send(sock, (uint8_t*)handshake.c_str(), handshake.size(), _FLAG);
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
    cout << "Connect: " << status << endl << "Socket: " << sock << endl ;
    if (status < 0) { 
        std::cout << "Unable to connect" << std::endl;
        cout << "Error NO: " << errno;
        return errno;
    }
    sendHeader();
    return 0;
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

int WebsocketClient::send() {
    // string raw = (string)"42[\"" + name + "\",\"" + data + "\"]";
    // const char * craw = raw.c_str();
    // if(::send(sock, craw, sizeof(craw), _FLAG) < 0) {
    //     return errno;
    // }
    return 0;
}

int WebsocketClient::ping() {
    return ::send(sock, "0", 1, _FLAG);
}
