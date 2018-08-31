#include <iostream>
#include "../include/JsonObject.h"

int main() {

    JsonObject restaurant;

    restaurant["name"] = "Cosmo";
    restaurant["opening date"] = 2007;
    restaurant["owner"] = JsonObject();
    restaurant["owner"]["name"] = "Max";
    restaurant["menu"] = {"Pizza", "Pasta", "Seafood"};
    restaurant["cat"] = nullptr;

    std::cout << restaurant.toString(4);

    return 0;
}