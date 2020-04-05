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
        throw ParseException("Invalid Json: object does not start with '{'");

    }
    if (getJson().at(lastPosition()) != ']') {
        throw ParseException("Invalid Json: array does not end with ']'");
    }
}
