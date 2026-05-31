#include "JsonArray.h"
#include "JsonNode.h"
#include <stdexcept>

const JsonValue& JsonArray::get(int idx)
{
    if (idx < 0 || idx >= arr.size())
        throw std::runtime_error(
            "Array index out of bounds");

    return arr[idx];
}

void JsonArray::insert(
    const JsonValue& value)
{
    arr.push_back(value);
}

void JsonArray::insert(const std::vector<JsonValue> &vals){
        arr.insert(arr.end(),vals.begin(),vals.end());
}

std::vector<JsonValue>& JsonArray::getArr()
{
    return arr;
}

void JsonNode::set(const std::string key,const std::vector<JsonValue> &values){
        std::shared_ptr<JsonArray> temp = std::make_shared<JsonArray>();

        for(auto &i : values){
            temp -> insert(i);
        }

        mp.emplace(key,temp);
}