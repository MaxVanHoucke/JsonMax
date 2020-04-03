//
// Created by max on 03/04/2020.
//

#include "ArrayParser.h"

using namespace JsonMax;

Element ArrayParser::parse() {
//    if (array.back() != ']') {
//        throw ParseException("Invalid Json: array does not end with '}'");
//    }
    Array array;
    while (not endOfParsing()) {
        std::string element = extractElementAndAdjustIndex();
        array.push_back(JsonMax::parse(element));
    }
    return array;
}
