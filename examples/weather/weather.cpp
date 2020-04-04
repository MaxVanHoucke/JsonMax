/**
 * Example that shows parsing and reading a json file
 */

#include <iostream>
#include "../../single_include/JsonMax.h"

using namespace JsonMax;

int main() {

    std::string fileName = "../../../examples/weather/weather.json";
    Object weather = parseFile(fileName).getObject();

    std::cout << "Type: " << weather["type"].getString() << std::endl;

    for (const Element& forecast: weather["days"].getArray()) {

        if (!forecast.isObject()) {
            continue;
        }

        for (const Pair& pair: forecast.getObject().pairs()) {
            std::cout << pair.getKey() << ": " << pair.getValue().toString() << std::endl;
        }
    }

    return 0;
}
