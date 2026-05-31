#pragma once

#include "JsonValue.h"
#include <ostream>

struct Visitor {
    std::ostream& out;
    int indent = 0;

    void operator()(std::nullptr_t);
    void operator()(const double&);
    void operator()(const std::string&);
    void operator()(bool);
    void operator()(const std::shared_ptr<JsonNode>&);
    void operator()(const std::shared_ptr<JsonArray>&);
};

std::ostream& operator<<(
    std::ostream& out,
    const JsonValue& value
);