# CSon

A lightweight C++ JSON parser, printer, and small in-memory JSON library.

CSon can be used both as a standalone parser/printer (see `main.cpp`) and
as an embeddable library for constructing, modifying, and printing JSON values
programmatically from your C++ projects.

## Features

- JSON objects and arrays
- strings, numbers, booleans, and null
- nested structure manipulation via `JsonNode` and `JsonArray`
- readable formatted printing via `JsonPrinter`
- root-object parsing from both brace-enclosed and direct key/value style input

## Project Structure

- `main.cpp` — sample program demonstrating parser usage
- `Makefile` — build rules for compilation and execution
- `include/` — public headers defining parser, printer, AST node, and value types
  - `JsonParser.h`
  - `JsonPrinter.h`
  - `JsonValue.h`
  - `JsonNode.h`
  - `JsonArray.h`
- `src/` — implementation files
  - `JsonParser.cpp`
  - `JsonPrinter.cpp`
  - `JsonNode.cpp`
  - `JsonArray.cpp`

## Build

Use the included `Makefile`:

```sh
make
```

This produces an executable named `json`.

## Run

Execute the compiled program:

```sh
./json
```

The current sample input in `main.cpp` parses and prints a JSON object.

## Using as a library

Include the headers from `include/` and link against the compiled sources (or include
the source files in your build). The library exposes a minimal API using `JsonValue`,
`JsonNode` and `JsonArray` which are defined in `include/`.

Minimal examples:

- Parse a string and print the resulting `JsonValue`:

```cpp
#include "JsonParser.h"
#include "JsonPrinter.h"
#include <iostream>

int main() {
    std::string json = " \"abc\" : \"pqr\" ";
    JsonParser parser(json);
    JsonValue root = parser.parse();
    std::cout << root << std::endl; // prints formatted JSON
}
```

- Construct and manipulate JSON programmatically:

```cpp
#include "JsonNode.h"
#include "JsonArray.h"
#include "JsonPrinter.h"
#include <memory>
#include <iostream>

int main() {
    auto node = std::make_shared<JsonNode>();
    node->set("name", std::string("Alice"));
    node->set("age", 30.0);

    auto arr = std::make_shared<JsonArray>();
    arr->insert(std::string("one"));
    arr->insert(2.0);

    node->set("items", arr);

    JsonValue root = node;
    std::cout << root << std::endl; // prints the object
}
```

Notes on types:

- Numbers are represented as `double`.
- Strings use `std::string`.
- Objects and arrays are `std::shared_ptr<JsonNode>` and `std::shared_ptr<JsonArray>` respectively.

## Example input

The parser can handle inputs such as:

```json
"abc" : "pqr"
```

and will print:

```json
{
    "abc": "pqr"
}
```

## Notes

- The parser currently supports a practical JSON subset with correct whitespace handling.
- String escape sequences are supported for common JSON escapes.
- The printer formats objects and arrays with indentation for readability.
