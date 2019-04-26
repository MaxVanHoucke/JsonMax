#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Object.h"
#include "../include/Parser.h"
#include "../include/Exceptions.h"

using namespace JsonMax;




int main(int argc, char** argv) {


    Object restaurant(Object::VECTOR);

    restaurant["name"] = "Cosmo";
    restaurant["opening date"] = 2007;
    restaurant["owner"] = Object(Object::VECTOR);
    restaurant["owner"]["name"] = "Max";
    restaurant["owner"]["money"] = 1;
    restaurant["food"] = {"Pizza", "Pasta", "Seafood"};

    std::cout << restaurant.toString();

//    std::ofstream out("resto.json");
//    out << restaurant.toString(4) << std::endl;
//    out.close();

/*
    std::string name = restaurant["name"].getString();
    Object obj = restaurant["owner"].getObject();
    for (auto elem: obj) {
        if (elem.key == "money") {

        }
    }
*/


//    Object pizza;
//    pizza["title"] = "Margherita";
//    pizza["ingredients"] = {"Mozarella", "Tomato Sauce"};
//    pizza["price"] = 8;
//
//    Object pizza2;
//    pizza2["title"] = "Vegetariana";
//    pizza2["ingredients"] = "Mozarella, tomato sauce, eggplant, zucchini, artichoke";
//    pizza2["price"] = 10;
//
//
//    restaurant["pizzas"] = {pizza, pizza2};
//    restaurant["cat"] = nullptr;
//
//    restaurant["owner"]["dog"] = Object();
//    restaurant["owner"]["dog"]["name"] = "Mino";
//    restaurant["owner"]["dog"]["age"] = 4;
//    restaurant["owner"]["dog"]["favorite food"] = Object();
//    restaurant["owner"]["dog"]["favorite food"]["title"] = "chicken";
//
//    std::string restoStr = restaurant.toString(4);
//
//    Object object = parse(restoStr);
//    std::cout << restaurant["owner"]["dog"].toString() << std::endl;

//    bool a = object["owner"]["dog"]["breh"];

    exit(0);

    if (argc < 3) {
        exit(0);
    }

    std::ifstream in;
    in.open(argv[2]);
    std::stringstream buffer;
    buffer << in.rdbuf();

    std::string json = buffer.str();

    Element element;

    bool valid = true;
    try {
        element = parse(json);
    } catch (ParseException& e) {
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