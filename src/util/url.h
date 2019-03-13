#ifndef URL_H
#define URL_H
#include <string>
using namespace std;

class URL {
public:
    string host;
    int port = 80;
    string uri;
    string protocol = "http";
    URL(string);
};

#endif