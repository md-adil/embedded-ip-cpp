#include "json.h"

JSON::JSON() {
}

JSON::JSON(cJSON * d) {
    _data = d;
}

JSON::JSON(string d) {
    _data = cJSON_Parse(d.c_str());
}

vector<JSON *> JSON::toArray() {
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

JSON * JSON::set(string key, JSON * data) {
	cJSON_AddItemToObject(_data, key.c_str(), data->_data);
	return this;
}
JSON * JSON::set(string key, string data) {
	cJSON_AddStringToObject(_data, key.c_str(), data.c_str());
	return this;
}


JSON * JSON::push(JSON * data) {
	cJSON_AddItemToArray(_data, data->_data);
	return this;
}

JSON * JSON::push(string data) {
	cJSON_AddItemToArray(_data, cJSON_CreateString(data.c_str()));
	return this;
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

JSON * JSON::Array() {
    return new JSON(cJSON_CreateArray());
}
JSON * JSON::Object() {
    return new JSON(cJSON_CreateObject());
}

void JSON::each(void(*callback)(string)) {
    cJSON * item;
    cJSON_ArrayForEach(item, _data) {
        callback(item->valuestring);
    }
}

string JSON::json() {
    return cJSON_PrintUnformatted(_data);
}
