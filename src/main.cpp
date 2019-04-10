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

int main() {
    WebsocketClient client((URL)"127.0.0.1:3000/socket.io/?transport=websocket");

    client.on("connect", []() {
        cout << "Conected successfully" << endl;
    });

    client.on("error", [](string message) {
        cout << "Error: " << message << endl;
    });

    client.on("hellos", [](string mes) {
        cout << "reading hello: " << mes << endl;
    });

    client.on("message", [](string message) {
        cout << "Message received: " << message << endl;
    });

    client.on("message", [](string message) {
        cout << "Again Same Message: " << message << endl;
    });

    thread sock([&]() {
        client.loop();
    });
    sock.join();
    
    return 0;
}

class App {
public:
    App() {
        cout << "COnstructed" << endl;
    }

    ~App() {
        cout << "DesCOnstructed" << endl;
    }

    void loop() {
        cout << "LOoping" << endl;
    }

    void operator()() {
        int x = 10;
        while(x--) {
            loop();
            sleep(1);
        }
    }
};

void runTask(App & app) {
    int x = 10;
    while(x--) {
        app.loop();
        sleep(1);
    }
}

int maini() {
    App app;
    thread t1([&]() {
       app();
    });
    t1.join();
    return 0;
}