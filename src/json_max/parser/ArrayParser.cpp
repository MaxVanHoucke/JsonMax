/**
 * @author Max Van Houcke
 */

#include <iostream>
#include "ArrayParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element ArrayParser::parse() {
    trim();
    if (currentSymbol() != '[') {
        throw ParseException("Invalid Json: object does not start with '{'");

    }

    incrementPosition();
    
    if (getJson().at(lastPosition()) != ']') {
        std::cout << getJson().substr(currentPosition(), remainingSize()) << std::endl;
        throw ParseException("Invalid Json: array does not end with ']'");
    }



    Array array;
    while (not endOfParsing()) {
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition();
        }
        array.push_back(Parser(getJson(), currentPosition(), endIndexOfElement - 1).parse());
        setPosition(endIndexOfElement + 1);
    }
    return array;
}
