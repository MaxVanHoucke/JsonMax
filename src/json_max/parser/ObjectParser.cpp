/**
 * @author Max Van Houcke
 */
#include "ObjectParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element ObjectParser::parse() {
    trim();
    if (currentSymbol() != '{') {
        throw ParseException("Invalid Json: object does not start with '{'");

    }

    incrementPosition();

    if (getJson().at(lastPosition()) != '}') {
        throw ParseException("Invalid Json: object does not end with '}'");
    }

    Element obj = Object();
    while (not endOfParsing()) {
        std::string key = extractKeyAndAdjustIndex();
        checkForDoublePointAndAdjustIndex();
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition() - 1;
        }
        obj[key] = Parser(getJson(), currentPosition(), endIndexOfElement).parse();
    }
    return obj;
}



std::string ObjectParser::extractKeyAndAdjustIndex() {
    // First quotation mark
    moveToNonEmptyPosition();
    if (endOfParsing() or currentSymbol() != '"') {
        throw ParseException("Invalid Json, missing key in object");
    }
    incrementPosition();

    int keyStart = currentPosition();

    // Second quotation mark
    setPosition(findIndexAfterElement('"'));
    if (endOfParsing()) {
        throw ParseException("Invalid Json, key in object has no ending");
    }
    incrementPosition();

    return getJson().substr(keyStart, currentPosition() - keyStart - 1);
}



void ObjectParser::checkForDoublePointAndAdjustIndex() {
    moveToNonEmptyPosition();
    if (endOfParsing() or currentSymbol() != ':') {
        throw ParseException("Invalid Json, no ':' between key and value");
    }
    incrementPosition();
}



