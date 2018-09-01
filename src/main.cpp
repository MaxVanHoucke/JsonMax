#include <iostream>
#include "../include/JsonObject.h"
#include "../include/JsonParser.h"

int main() {

    JsonObject restaurant;

    restaurant["name"] = "Cosmo";
    restaurant["opening date"] = 2007;
    restaurant["owner"] = JsonObject();
    restaurant["owner"]["name"] = "Max";
//    restaurant["food"] = {"Pizza", "Pasta", "Seafood"};

    JsonObject pizza;
    pizza["title"] = "Margherita";
    pizza["ingredients"] = {"Mozarella", "Tomato Sauce"};
    pizza["price"] = 8;

    JsonObject pizza2;
    pizza2["title"] = "Vegetariana";
    pizza2["ingredients"] = "Mozarella, tomato sauce, eggplant, zucchini, artichoke";
    pizza2["price"] = 10;

    restaurant["pizzas"] = {pizza, pizza2};
    restaurant["cat"] = nullptr;

    restaurant["owner"]["dog"] = JsonObject();
    restaurant["owner"]["dog"]["name"] = "Mino";
    restaurant["owner"]["dog"]["age"] = 4;
    restaurant["owner"]["dog"]["favorite food"] = JsonObject();
    restaurant["owner"]["dog"]["favorite food"]["title"] = "chicken";

    std::string restoStr = restaurant.toString(4);

    JsonObject object = JsonParser::parse(restoStr);
    std::cout << object.toString(4);

//    bool a = object["owner"]["dog"]["breh"];

    return 0;
}