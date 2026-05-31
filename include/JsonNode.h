#pragma once
#include "JsonValue.h"
#include <unordered_map>
#include <stdexcept>

class JsonNode {
private:
    std::unordered_map<std::string, JsonValue> mp;

public:
    const JsonValue& get(const std::string& key);
    void set(const std::string& key, const JsonValue& value);
    void set(const std::string key,const std::vector<JsonValue> &values);

    std::unordered_map<std::string, JsonValue>& getMap();
};