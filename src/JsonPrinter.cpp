#include "JsonPrinter.h"
#include "JsonNode.h"
#include "JsonArray.h"

#include <variant>
#include <memory>
#include <string>

static std::string tabs(int n)
{
    return std::string(n, '\t');
}

void Visitor::operator()(std::nullptr_t)
{
    out << "null";
}

void Visitor::operator()(const double& x)
{
    out << x;
}

void Visitor::operator()(const std::string& str)
{
    out << '"' << str << '"';
}

void Visitor::operator()(bool val)
{
    out << (val ? "true" : "false");
}

void Visitor::operator()(const std::shared_ptr<JsonNode>& value)
{
    out << "{\n";

    auto& mp = value->getMap();

    size_t count = 0;
    size_t total = mp.size();

    for (const auto& [k, v] : mp)
    {
        out << tabs(indent + 1)
            << '"' << k << '"' << ": ";

        std::visit(Visitor{out, indent + 1}, v);

        if (++count < total)
            out << ",";

        out << "\n";
    }

    out << tabs(indent) << "}";
}

void Visitor::operator()(const std::shared_ptr<JsonArray>& value)
{
    out << "[\n";

    auto& arr = value->getArr();

    for (size_t i = 0; i < arr.size(); i++)
    {
        out << tabs(indent + 1);

        std::visit(Visitor{out, indent + 1}, arr[i]);

        if (i + 1 < arr.size())
            out << ",";

        out << "\n";
    }

    out << tabs(indent) << "]";
}

std::ostream& operator<<(
    std::ostream& out,
    const JsonValue& value)
{
    std::visit(Visitor{out, 0}, value);
    return out;
}