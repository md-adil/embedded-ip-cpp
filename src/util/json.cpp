#include "json.h"

JSON::JSON() {
}

JSON::JSON(cJSON * d) {
    _data = d;
}

JSON::JSON(string d) {
    _data = cJSON_Parse(d.c_str());
}

vector<JSON *> JSON::getArray(string key) {
    vector<JSON *> items;
    cJSON * item;
    cJSON_ArrayForEach(item, _data) {
        items.push_back(new JSON(item));
    }
    return items;
}

// Premitive data types
JSON * JSON::get(string key) {
    return new JSON(
        cJSON_GetObjectItemCaseSensitive(_data, key.c_str())
    );
}

int JSON::toNumber() {
    return _data->valueint;
}

double JSON::toDouble() {
    return _data->valuedouble;
}


bool JSON::isNumber() {
    return (_data->type & 0xFF) == cJSON_Number;
}

bool JSON::isString() {
    return (_data->type & 0xFF) == cJSON_String;
}

bool JSON::isObject() {
    return (_data->type & 0xFF) == cJSON_Object;
}

bool JSON::isBool() {
    if (_data == NULL) {
        return false;
    }
    return (_data->type & (cJSON_True | cJSON_False)) != 0;
}

string JSON::toString() {
    return (string)_data->valuestring;
}

string JSON::pretty() {
    return (string)cJSON_Print(_data);
}
