#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>

class JsonNode;
class JsonArray;

using JsonValue = std::variant<
    std::nullptr_t,
    double,
    std::string,
    bool,
    std::shared_ptr<JsonNode>,
    std::shared_ptr<JsonArray>
>;