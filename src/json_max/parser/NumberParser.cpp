/**
 * @author Max Van Houcke
 */

#include "NumberParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element NumberParser::parse() {
    trim();
    double number = parseNumber();
    if (getJson().find(".", currentPosition(), remainingSize()) == std::string::npos) {
        return Element((int) number);
    } else {
        return Element(number);
    }
}

double NumberParser::parseNumber() const {
    std::string stringValue = getJson().substr(currentPosition(), remainingSize());
    try {
        return std::stod(stringValue);
    } catch (std::out_of_range &e) {
        throw ParseException("Cannot parse, number '" + stringValue + "' is out of range.");
    } catch (std::invalid_argument &e) {
        throw ParseException("Invalid Json, '" + stringValue + "' is not valid.");
    }
}
