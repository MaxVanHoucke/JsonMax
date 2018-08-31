#include <iostream>
#include "../include/JsonObject.h"

int main() {

    JsonObject object;
    object["test"] = "hmm";
    object["what"] = 5;
    object["test"] = "blah";

    JsonObject other;
    other["name"] = "Max";

    object["person"] = other;

    object["person"]["age"] = 19;
    object["person"]["dog"] = JsonObject();
    object["person"]["dog"]["sound"] = true;

    object["blah"] = "hmmmm";

//    auto a = object["person"];
//    a["age"] = 19;

    std::cout << object.toString();

    return 0;
}