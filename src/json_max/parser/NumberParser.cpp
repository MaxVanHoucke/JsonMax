//
// Created by max on 03/04/2020.
//

#include "NumberParser.h"

using namespace JsonMax;

Element NumberParser::parse() {
    double number;
    try {
        number = std::stod(element);
    } catch (std::out_of_range &e) {
        throw ParseException("Cannot parse, number '" + element + "' is out of range.");
    } catch (std::invalid_argument &e) {
        throw ParseException("Invalid Json, number '" + element + "' is not valid.");
    }

    if (element.find('.') == std::string::npos) {
        return Element((int) number);
    } else {
        return Element(number);
    }
}
