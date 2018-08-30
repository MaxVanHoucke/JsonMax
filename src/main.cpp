#include <iostream>
#include "../include/JsonObject.h"

int main() {

    JsonObject object;
    object["test"] = "hmm";
    object["what"] = 5;
    object["test"] = false;
    JsonObject other;
    other["name"] = "Max";
    object["person"] = other;
    std::cout << object.toString();

//    std::string a;
//    std::string& b = a;
//    std::cout << &a << std::endl;
//    std::cout << &b;

    return 0;
}