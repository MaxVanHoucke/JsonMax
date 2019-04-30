#include <iostream>
#include <fstream>
#include <sstream>
#include "Object.h"
#include "Parser.h"
#include "Exceptions.h"

using namespace JsonMax;


int main(int argc, char** argv) {



    try {
        // I forgot a '}' at the end of my string
        Element element = parse(R"( {"test": "a" )");
    } catch (ParseException& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}
