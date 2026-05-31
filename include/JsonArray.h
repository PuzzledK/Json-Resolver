#pragma once

#include "JsonValue.h"
#include <vector>

class JsonArray {
private:
    std::vector<JsonValue> arr;

public:
    const JsonValue& get(int index);

    void insert(const JsonValue& value);
    void insert(const std::vector<JsonValue> &vals);

    std::vector<JsonValue>& getArr();
};