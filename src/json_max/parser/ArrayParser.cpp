/**
 * @author Max Van Houcke
 */

#include "ArrayParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element ArrayParser::parse() {
    trim();
    if (getJson().at(lastPosition()) != ']') {
        throw ParseException("Invalid Json: array does not end with '}'");
    }

    Array array;
    while (not endOfParsing()) {
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition() - 1;
        }
        array.push_back(Parser(getJson(), currentPosition(), endIndexOfElement).parse());
    }
    return array;
}
