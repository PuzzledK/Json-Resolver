#include "JsonNode.h"
#include <stdexcept>

const JsonValue& JsonNode::get(const std::string& key)
{
    auto it = mp.find(key);

    if (it == mp.end())
        throw std::runtime_error("Key not found");

    return it->second;
}

void JsonNode::set(
    const std::string& key,
    const JsonValue& value)
{
    mp[key] = value;
}

std::unordered_map<std::string, JsonValue>&
JsonNode::getMap()
{
    return mp;
}