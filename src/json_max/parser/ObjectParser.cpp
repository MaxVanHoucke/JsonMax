/**
 * @author Max Van Houcke
 */

#include <iostream>
#include "ObjectParser.h"
#include "ParseException.h"

using namespace JsonMax;

Element ObjectParser::parse() {
    trim();
    checkObjectSemantics();
    incrementPosition();

    Object obj = Object();
    while (not endOfParsing()) {
        std::string key = extractKeyAndAdjustIndex();
        checkForDoublePointAndAdjustIndex();
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition();
        }
        obj[key] = Parser(getJson(), currentPosition(), endIndexOfElement).parse();
        setPosition(endIndexOfElement + 1);
    }
    return obj;
}



std::string ObjectParser::extractKeyAndAdjustIndex() {
    // First quotation mark
    moveToNonEmptyPosition();
    if (endOfParsing() or currentSymbol() != '"') {
        throwException("Invalid Json, missing key in object");
    }
    incrementPosition();

    int keyStart = currentPosition();

    // Second quotation mark
    setPosition(findIndexAfterElement('"'));
    if (endOfParsing()) {
        throwException("Invalid Json, key in object has no ending");
    }
    incrementPosition();

    return getJson().substr(keyStart, currentPosition() - keyStart - 1);
}



void ObjectParser::checkForDoublePointAndAdjustIndex() {
    moveToNonEmptyPosition();
    if (endOfParsing() or currentSymbol() != ':') {
        throwException("Invalid Json, no ':' between key and value");
    }
    incrementPosition();
}

void ObjectParser::checkObjectSemantics() {
    if (currentSymbol() != '{') {
        throwException("Invalid Json: object does not start with '{'");

    }
    if (getJson().at(lastPosition()) != '}') {
        throwException("Invalid Json: object does not end with '}'");
    }
}



