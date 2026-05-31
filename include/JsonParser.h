#pragma once

#include "JsonValue.h"
#include <string>

class JsonParser {
private:
    std::string input;
    size_t pos;

public:
    JsonParser(const std::string& s);

    JsonValue parse();

private:
    JsonValue parseValue();

    std::shared_ptr<JsonNode> parseObject(bool expectBraces = true);
    std::shared_ptr<JsonArray> parseArray();

    std::string parseString();
    double parseNumber();

    void skipWhitespace();

    char peek();
    char consume();
    bool startsWith(const std::string& prefix) const;
    void expect(char expected);
};