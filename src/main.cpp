#include <iostream>
#include "util/json.h"
using namespace std;

int main() {
    string jsondata = "{\"name\": \"Adil\"}";
    JSON * json = new JSON(jsondata);
    json->set("hey", "There");
    json->set("roles", JSON::Array());
    json->get("roles")->push("hello");
    json->get("roles")->push("World");
    json->get("roles")->push("this is Adil");

    cout << json->json() << endl;
    return 0;
}
