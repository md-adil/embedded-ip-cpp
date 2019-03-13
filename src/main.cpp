#include <iostream>
#include "util/json.h"
using namespace std;

int main() {
    string jsondata = "{\"name\": \"Adil\"}";
    JSON * json = new JSON(jsondata);
    bool name = json->get("name")->isNumber();
    cout << "Name: " <<  name << endl;
    return 0;
}
