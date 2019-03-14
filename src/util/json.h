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

    JSON * set(string, JSON*);
    JSON * set(string, string);
    JSON * push(JSON*);
    JSON * push(string);
    vector<JSON *> toArray();
    string pretty();
    string toString();
    bool isNumber();
    void each(void(*cb)(JSON*));
    void each(void(*cb)(string));
    bool isString();
    bool isObject();
    bool isArray();
    bool isBool();
    int toNumber();
    double toDouble();
    string json();
    static JSON * Array();
    static JSON * Object();
private:
    cJSON * _data;
};

#endif
