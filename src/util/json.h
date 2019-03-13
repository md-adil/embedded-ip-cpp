#ifndef JSON_H
#define JSON_H
#include <string>
#include <vector>
#include <cjson/cJSON.h>

using namespace std;

class JSON {
public:
    JSON();
    JSON(string);
    JSON(cJSON *);
    JSON(JSON *);
    JSON * remove(string);
    JSON * get(string);
    vector<JSON *> getArray(string);
    string pretty();
    string toString();
    bool isNumber();
    bool isString();
    bool isObject();
    bool isArray();
    bool isBool();
    int toNumber();
    double toDouble();

private:
    cJSON * _data;
};

#endif