#include <iostream>
#include <string>
#include <unistd.h>
#include "util/random.h"
#include "util/json.h"
#include "util/base64.h"
#include "websocket/client.h"

using namespace std;

int main() {
    WebsocketClient client((URL)"127.0.0.1:3000/socket.io/?transport=websocket");

    client.on("connect", []() {
        cout << "Conected successfully" << endl;
    });

    client.on("error", [](string message) {
        cout << "Error: " << message << endl;
    });

    client.on("message", [](string message) {
        cout << "Message received: " << message << endl;
    });

    client.on("hello", [](string mes) {
        cout << "reading hello: " << mes;
    });
    
    while(true) {
        client.loop();
    }
   
    return 0;
}

int mainold() {
    char data[15] = {'a', 'd', 'i', 'l'};

    cout << data << ':' << strlen(data) << endl;
    return 0;
}