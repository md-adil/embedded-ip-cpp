```c++

#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <ctime>
#include "util/random.h"
#include "util/json.h"
#include "util/base64.h"
#include "websocket/client.h"

using namespace std;

void clientLoop(WebsocketClient & client) {
    while(true) {
        client.loop();
        sleep(1);
    }
}
char * userName;

void waitForMessage(WebsocketClient & client, string name) {
    cout.flush();
    cout << name << ">> " << flush;
    string message;
    getline(cin, message);
    JSON payload = JSON::Object();
    payload.set("name", name);
    payload.set("message", message);
    client.emit("message", payload);
}

int main() {
    cout << "Enter your name: " << flush;
    string name;
    getline(cin, name);

    WebsocketClient client((URL)"127.0.0.1:3000/socket.io/?transport=websocket");

    client.on("connect", []() {
        cout << "Conected successfully" << endl;
    });

    client.on("error", [](string message) {
        cout << "Error: " << message << endl;
    });

    client.on("message", [](JSON message) {
        cout << message.get("name").toString() << ">>" << message.get("message").toString() << endl;
    });

    thread sock([&]() {
        client.loop();
    });

    while(true) {
        waitForMessage(client, name);
    }

    sock.join();
    
    return 0;
}

```
