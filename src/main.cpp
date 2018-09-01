#include <iostream>
#include "../include/JsonObject.h"

int main() {

    JsonObject restaurant;

    restaurant["name"] = "Cosmo";
    restaurant["opening date"] = 2007;
    restaurant["owner"] = JsonObject();
    restaurant["owner"]["name"] = "Max";
    restaurant["food"] = {"Pizza", "Pasta", "Seafood"};

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

    std::cout << restaurant.toString(4);

    return 0;
}