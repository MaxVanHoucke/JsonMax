//
// Created by max on 03/04/2020.
//

#include "StringParser.h"

using namespace JsonMax;

Element StringParser::parse() {
    if (isValidString()) {
        std::string jsonStringWithoutQuotations = string.substr(1, string.size() - 2);
        return Element(jsonStringWithoutQuotations);
    }
    throw ParseException("Invalid Json, string " + string + " is invalid as per Json rules.");
}

bool StringParser::isValidString() {
    if (input.size() < 2 or input.front() != '"' or input.back() != '"') {
        return false;
    }

    bool escape = false;
    for (size_t i = 1; i < input.size() - 1; i++) {
        char symbol = input[i];
        if (escape) {
            if (not escapedStringPartIsValid(input, i)) {
                return false;
            }
            escape = false;
        } else if (symbol == '\\') {
            escape = true;
        } else if (symbol == '\"') {
            return false;
        }
    }
    return true;
}


bool StringParser::isHexadecimalCorrect() {
    if (index + 4 >= input.size()) {
        return false;
    }
    const static std::string hexa = "0123456789abcdefABCDEF";
    size_t result = input.find_first_not_of(hexa.c_str(), index + 1, 4);
    return result != std::string::npos;
}


bool StringParser::isEscapedPartCorrect() {
    char symbol = input[index];
    // Allowed chars after escape
    const static std::string allowed = "\"\\/bfnrtu";
    if (allowed.find(symbol) == std::string::npos) {
        return false;
    }
    // u has to be followed by 4 hexadecimal units
    return symbol != 'u' or escapedHexadecimalIsCorrect(input, index);
}
