#include "client.h"

WebsocketClient::WebsocketClient() {
    std::cout << "Intialin" << std::endl;
}

WebsocketClient::WebsocketClient(string _url) {
    url = new URL(_url);
}

WebsocketClient::WebsocketClient(URL _url) {
    url = &_url;
}

int WebsocketClient::connect(string url) {
    cout << "Connecting to url " << url << endl;
    return 0;
}

