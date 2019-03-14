#include <iostream>
#include <unistd.h>
#include "websocket/client.h"
#include "util/json.h"
using namespace std;

int main() {
    WebsocketClient io = (string)"http://127.0.0.1:3000/socket.io/?transport=websocket";

    io.on("connect", []() {
        cout << "Connected to client" << endl;
    });

    io.on("error", [](string message) {
        cout << "Error: " << message << endl;
    });
    io.connect();
    cout << "REading header: " << endl;
    io.read();
    cout << "REading body: " << endl;
    io.read();
    // while(1) {
    //     sleep(10);
    // }
    return 0;
}
