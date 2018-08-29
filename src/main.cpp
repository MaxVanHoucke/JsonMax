#include <iostream>
#include "../include/JsonObject.h"

int main() {
//    JsonObject object;
//    object["jtest"];
    JsonObject* object = new JsonObject();
    (*object)["test"];
    std::cout << "Hello, World!" << std::endl;
    return 0;
}