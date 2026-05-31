#include "JsonParser.h"
#include "JsonPrinter.h"

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

    file.close();

    JsonParser parser(json);

    JsonValue root =
        parser.parse();

    std::cout << root << '\n';
}