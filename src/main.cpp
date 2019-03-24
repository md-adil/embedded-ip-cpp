#include <iostream>
#include "util/random.h"
#include "util/json.h"
#include "util/base64.h"
#include "websocket/client.h"
#include <string>
#include <unistd.h>

using namespace std;

int main() {
    WebsocketClient io = (string)"127.0.0.1:3000/socket.io/?transport=websocket";
    io.connect();

    JSON data = JSON::Object();
    data.set("name", "Adil");
    data.set("roll", "Developer");

    // sleep(1);
    io.ping();

    io.emit("msg", "hello world this is Adil");
    while(io.read()) {}
    return 0;
}
