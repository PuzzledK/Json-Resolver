#include "JsonParser.h"
#include "JsonArray.h"
#include "JsonNode.h"

#include <cctype>
#include <stdexcept>

JsonParser::JsonParser(
    const std::string& s)
    : input(s), pos(0){}

void JsonParser::skipWhitespace()
{
    while (
        pos < input.size() &&
        std::isspace(static_cast<unsigned char>(input[pos])))
    {
        pos++;
    }
}

char JsonParser::peek()
{
    skipWhitespace();
    if (pos >= input.size())
        return '\0';

    return input[pos];
}

char JsonParser::consume()
{
    if (pos >= input.size())
        throw std::runtime_error("Unexpected end of input");

    return input[pos++];
}

bool JsonParser::startsWith(const std::string& prefix) const
{
    return input.compare(pos, prefix.size(), prefix) == 0;
}

void JsonParser::expect(char expected)
{
    if (peek() != expected)
        throw std::runtime_error(std::string("Expected '") + expected + "'");

    consume();
}

std::string JsonParser::parseString()
{
    expect('"');

    std::string result;

    while (true)
    {
        if (pos >= input.size())
            throw std::runtime_error("Unterminated string");

        char c = consume();

        if (c == '"')
            break;

        if (c == '\\')
        {
            if (pos >= input.size())
                throw std::runtime_error("Unterminated escape sequence");

            char esc = consume();
            switch (esc)
            {
            case '"': result += '"'; break;
            case '\\': result += '\\'; break;
            case '/': result += '/'; break;
            case 'b': result += '\b'; break;
            case 'f': result += '\f'; break;
            case 'n': result += '\n'; break;
            case 'r': result += '\r'; break;
            case 't': result += '\t'; break;
            default:
                throw std::runtime_error("Invalid escape sequence");
            }
        }
        else
        {
            result += c;
        }
    }

    return result;
}

double JsonParser::parseNumber()
{
    size_t start = pos;

    if (peek() == '-')
        consume();

    if (peek() == '0')
    {
        consume();
    }
    else if (std::isdigit(peek()))
    {
        while (std::isdigit(peek()))
            consume();
    }
    else
    {
        throw std::runtime_error("Invalid number");
    }

    if (peek() == '.')
    {
        consume();
        if (!std::isdigit(peek()))
            throw std::runtime_error("Invalid number");

        while (std::isdigit(peek()))
            consume();
    }

    if (peek() == 'e' || peek() == 'E')
    {
        consume();
        if (peek() == '+' || peek() == '-')
            consume();

        if (!std::isdigit(peek()))
            throw std::runtime_error("Invalid number");

        while (std::isdigit(peek()))
            consume();
    }

    return std::stod(input.substr(start, pos - start));
}

std::shared_ptr<JsonArray>
JsonParser::parseArray()
{
    expect('[');

    auto arr = std::make_shared<JsonArray>();

    skipWhitespace();

    if (peek() == ']')
    {
        consume();
        return arr;
    }

    while (true)
    {
        arr->insert(parseValue());

        skipWhitespace();

        if (peek() == ']')
        {
            consume();
            break;
        }

        expect(',');
    }

    return arr;
}

std::shared_ptr<JsonNode>
JsonParser::parseObject(bool expectBraces)
{
    if (expectBraces)
        expect('{');
    else if (peek() == '{')
        consume();

    auto obj = std::make_shared<JsonNode>();

    skipWhitespace();

    if (expectBraces && peek() == '}')
    {
        consume();
        return obj;
    }

    while (true)
    {
        std::string key = parseString();

        skipWhitespace();
        expect(':');

        obj->set(key, parseValue());

        skipWhitespace();
        char c = peek();

        if (c == ',')
        {
            consume();
            continue;
        }

        if (expectBraces)
        {
            if (c == '}')
            {
                consume();
                break;
            }

            throw std::runtime_error("Invalid JSON object");
        }

        if (c == '\0')
            break;

        throw std::runtime_error("Invalid JSON object");
    }

    return obj;
}

JsonValue JsonParser::parseValue()
{
    skipWhitespace();

    char c = peek();

    if (c == '{')
        return parseObject();

    if (c == '[')
        return parseArray();

    if (c == '"')
    {
        size_t save = pos;
        std::string key = parseString();
        skipWhitespace();

        if (peek() == ':')
        {
            pos = save;
            return parseObject(false);
        }

        pos = save;
        return parseString();
    }

    if (c == '-' || std::isdigit(static_cast<unsigned char>(c)))
        return parseNumber();

    if (startsWith("null"))
    {
        pos += 4;
        return nullptr;
    }

    if (startsWith("true"))
    {
        pos += 4;
        return true;
    }

    if (startsWith("false"))
    {
        pos += 5;
        return false;
    }

    throw std::runtime_error("Invalid JSON value");
}

JsonValue JsonParser::parse()
{
    JsonValue value = parseValue();
    skipWhitespace();

    if (pos != input.size())
        throw std::runtime_error("Trailing characters after JSON value");

    return value;
}