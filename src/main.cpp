#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/JsonObject.h"
#include "../include/JsonParser.h"

int main(int argc, char** argv) {

//    JsonObject restaurant;
//
//    restaurant["name"] = "Cosmo";
//    restaurant["opening date"] = 2007;
//    restaurant["owner"] = JsonObject();
//    restaurant["owner"]["name"] = "Max";
////    restaurant["food"] = {"Pizza", "Pasta", "Seafood"};
//
//    JsonObject pizza;
//    pizza["title"] = "Margherita";
//    pizza["ingredients"] = {"Mozarella", "Tomato Sauce"};
//    pizza["price"] = 8;
//
//    JsonObject pizza2;
//    pizza2["title"] = "Vegetariana";
//    pizza2["ingredients"] = "Mozarella, tomato sauce, eggplant, zucchini, artichoke";
//    pizza2["price"] = 10;
//
//    restaurant["pizzas"] = {pizza, pizza2};
//    restaurant["cat"] = nullptr;
//
//    restaurant["owner"]["dog"] = JsonObject();
//    restaurant["owner"]["dog"]["name"] = "Mino";
//    restaurant["owner"]["dog"]["age"] = 4;
//    restaurant["owner"]["dog"]["favorite food"] = JsonObject();
//    restaurant["owner"]["dog"]["favorite food"]["title"] = "chicken";
//
//    std::string restoStr = restaurant.toString(4);
//
//    JsonObject object = JsonParser::parse(restoStr);
//    std::cout << object.toString(4);

//    bool a = object["owner"]["dog"]["breh"];

//    exit(0);

    if (argc < 3) {
        exit(0);
    }

    std::ifstream in;
    in.open(argv[2]);
    std::stringstream buffer;
    buffer << in.rdbuf();

    std::string json = buffer.str();

    JsonElement element;

    bool valid = true;
    try {
        element = JsonParser::parse(json);
    } catch (JsonParser::JsonParsingException& e) {
        std::cout << e.what() << std::endl;
        valid = false;
    }

    if (argv[1] == std::string("validate")) {
        if (valid) {
            std::cout << "Valid JSON" << std::endl;
        }
    }
    else if (argv[1] == std::string("format")) {
        int indent = 4;
        if (argc == 4) {
            try {
                indent = std::stoi(argv[3]);
            } catch (...) {}
        }
        std::cout << element.toString(indent) << std::endl;
    }

    return 0;
}