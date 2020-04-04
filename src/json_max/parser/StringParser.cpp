/**
 * @author Max Van Houcke
 */

#include "StringParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element StringParser::parse() {
    trim();
    if (not isValidString()) {
        throw ParseException("Invalid Json, string  is invalid as per Json rules.");
    }
    return getJson().substr(currentPosition(), remainingSize());
}

bool StringParser::isValidString() {
    if (remainingSize() < 2 or currentSymbol() != '"' or getJson().at(lastPosition()) != '"') {
        return false;
    }

    bool escape = false;
    while (not endOfParsing()) {
        if (escape) {
            if (not isEscapedPartCorrect()) {
                return false;
            }
            escape = false;
        } else if (currentSymbol() == '\\') {
            escape = true;
        } else if (currentSymbol() == '\"') {
            return false;
        }
        incrementPosition();
    }
    return true;
}


bool StringParser::isHexadecimalCorrect() {
    if (currentPosition() + 4 > lastPosition()) {
        return false;
    }
    incrementPosition();
    const static std::string hexa = "0123456789abcdefABCDEF";
    size_t result = getJson().find_first_not_of(hexa.c_str(), currentPosition(), 4);
    return result != std::string::npos;
}


bool StringParser::isEscapedPartCorrect() {
    // Allowed chars after escape
    const static std::string allowed = "\"\\/bfnrtu";
    if (allowed.find(currentSymbol()) == std::string::npos) {
        return false;
    }
    // u has to be followed by 4 hexadecimal units
    return currentSymbol() != 'u' or isHexadecimalCorrect();
}
