#ifndef JSON_H
#define JSON_H
#include <iostream>
#include <string>
#include <vector>
#include <cjson/cJSON.h>

using namespace std;

class JSON {
public:
    JSON();
    JSON(string);
    JSON(cJSON *);
    JSON & remove(string);
    JSON get(string);

    JSON & set(const string &, JSON);
    JSON & set(const string &, const string &);
    JSON & push(JSON &);
    JSON & push(const string &);
    vector<JSON> toArray();
    string pretty();
    string toString();
    bool isNumber();
    void each(void(*cb)(JSON));
    void each(void(*cb)(string));
    bool isString();
    bool isObject();
    bool isArray();
    bool isBool();
    int toNumber();
    double toDouble();
    void clean();
    string json();
    static JSON parse(const string & str);
    static JSON Array();
    static JSON Object();
private:
    cJSON * _data = nullptr;
};

#endif
