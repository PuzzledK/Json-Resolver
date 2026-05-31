# Json Resolver

A lightweight C++ JSON parser and printer library with support for:
- JSON objects and arrays
- strings, numbers, booleans, and null
- nested structure printing with readable formatting
- root object parsing from both brace-enclosed and direct key/value style input

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
- `json/` — sample JSON data or supporting files
- `temp.json` — temporary JSON example file

## Build

Use the included `Makefile`:

```sh
make
```

This produces an executable named `json`.

## Run

Execute the compiled program:

```shn
./json
```

The current sample input in `main.cpp` parses and prints a JSON object.

## Example

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

- The parser currently supports a simple JSON subset with proper whitespace handling.
- String escape sequences are supported for common JSON escapes.
- The printer formats objects and arrays with indentation for readability.

## License

No license is specified. Add a `LICENSE` file if you want to define usage terms.
