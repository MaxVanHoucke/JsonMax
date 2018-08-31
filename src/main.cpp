#include <iostream>
#include "../include/JsonObject.h"

int main() {

    JsonObject object;
    object["test"] = "hmm";
    object["what"] = 5;
    object["test"] = "blah";

    object["person"] = JsonObject();
    object["person"]["age"] = 19;
    object["person"]["dog"] = JsonObject();
    object["person"]["dog"]["sound"] = true;


    object["blah"].setNULL();

    JsonObject wa;
    wa["hmm"] = "e2";
    wa["hsdf"];

    object["person"]["things"] = {3, "test", wa};

    std::cout << object.toString(4);

    return 0;
}