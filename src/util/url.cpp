#include "url.h"

URL::URL(string url) {
    size_t pos;
    pos = url.find("://");
    if(pos != string::npos) {
        protocol = url.substr(0, pos);
        url = url.substr(pos + 3, url.size());
    }
    pos = url.find('/');
    if(pos != string::npos) {
        host = url.substr(0, pos);
        uri = url.substr(pos, url.size());
    }
    pos = host.find(':');
    if(pos != string::npos) {
        port = stoi(host.substr(pos + 1, host.size()));
        host = host.substr(0, pos);
    }
}
