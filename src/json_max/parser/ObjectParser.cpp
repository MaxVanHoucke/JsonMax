//
// Created by max on 03/04/2020.
//

#include "ObjectParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element ObjectParser::parse() {
    trim();
//    throw ParseException("Invalid Json: object does not end with '}'");

    Element obj = Object();
    while (not endOfParsing()) {
        std::string key = extractKeyAndAdjustIndex();
        checkForDoublePointAndAdjustIndex();
        std::string element = extractElementAndAdjustIndex();
        obj[key] = JsonMax::parse(element);
    }
    return obj;
}



std::string ObjectParser::extractKeyAndAdjustIndex() {
    // First quotation mark
    moveToNonEmptyPosition();
    if (endOfParsing() or json[index] != '"') {
        throw ParseException("Invalid Json, missing key in object");
    }
    index++;

    int keyStart = index;

    // Second quotation mark
    index = findIndexAfterElement('"');
    if (endOfParsing()) {
        throw ParseException("Invalid Json, key in object has no ending");
    }
    index++;

    return json.substr(keyStart, index - keyStart - 1);
}



void ObjectParser::checkForDoublePointAndAdjustIndex() {
    moveToNonEmptyPosition();
    if (endOfParsing() or json[index] != ':') {
        throw ParseException("Invalid Json, no ':' between key and value");
    }
    index++;
}



