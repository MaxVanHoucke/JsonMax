/**
 * @author Max Van Houcke
 */

#include <iostream>
#include "ArrayParser.h"
#include "ParseException.h"

using namespace JsonMax;

Element ArrayParser::parse() {
    trim();
    checkArraySemantics();
    // Skip '['
    incrementPosition();

    Array array;
    while (not endOfParsing()) {
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition();
        }
        array.push_back(Parser(getJson(), currentPosition(), endIndexOfElement).parse());
        setPosition(endIndexOfElement + 1);
    }
    return array;
}

void ArrayParser::checkArraySemantics() {
    if (currentSymbol() != '[') {
        throwException("Array does not start with '{'");
    }
    if (getJson().at(lastPosition()) != ']') {
        throwException("Array does not end with ']'");
    }
}
