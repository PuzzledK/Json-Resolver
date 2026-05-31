#include "JsonParser.h"
#include "JsonPrinter.h"
#include "JsonNode.h"
#include "JsonArray.h"

#include <iostream>
#include <fstream>

int main(int argc,char** argv)
{
    if(argc < 2){
        throw std::runtime_error("No file passed as argument");
    }

    std::fstream file(argv[1],std::ios::in);
    std::string json;
    std::string temp;
    while(getline(file,temp)){
        json += temp;
    }

    std::fstream output_file("output.json",std::ios::out);

    JsonParser parser(json);

    std::shared_ptr<JsonNode> root = std::get<std::shared_ptr<JsonNode>>(parser.parse());

    std::shared_ptr<JsonArray> tempArr = std::make_shared<JsonArray>();
    tempArr -> insert("1");
    tempArr -> insert("2");
    tempArr -> insert("3");

    root -> set("Numbers",tempArr);

    output_file << (JsonValue) root << '\n';

    output_file.close();
    file.close();
}