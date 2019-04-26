#include <iostream>
#include <fstream>
#include <sstream>
#include "Object.h"
#include "Parser.h"
#include "Exceptions.h"

using namespace JsonMax;


int main(int argc, char** argv) {

    Object restaurant;

    restaurant["name"] = "Cosmo";
    restaurant["opening date"] = 2007;

    Object pizza;
    pizza["title"] = "Margherita";
    pizza["ingredients"] = {"Mozarella", "Tomato Sauce"};
    pizza["price"] = 8.5;

    Object pizza2;
    pizza2["title"] = "Siciliana";
    pizza2["ingredients"] = {"Mozarella", "Tomato Sauce", "Eggplant", "Parmigiano"};
    pizza2["price"] = 10;

    restaurant["pizzas"] = {pizza, pizza2};
    restaurant["cat"] = nullptr;

    restaurant["owner"] = Object();
    restaurant["owner"]["name"] = "Max";
    restaurant["owner"]["job"] = "Manager";

    std::cout << restaurant.toString(2) << std::endl;

    return 0;
}
