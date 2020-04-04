/**
 * @author Max Van Houcke
 */

#include "NumberParser.h"
#include "../Exceptions.h"

using namespace JsonMax;

Element NumberParser::parse() {
    trim();
    std::string str = getJson().substr(currentPosition(), remainingSize());
    double number = parseNumber(str);
    if (str.find('.') == std::string::npos) {
        return Element((int) number);
    } else {
        return Element(number);
    }
}

double NumberParser::parseNumber(const std::string& str) {
    try {
        return std::stod(str);
    } catch (std::out_of_range &e) {
        throw ParseException("Cannot parse, number '" + str + "' is out of range.");
    } catch (std::invalid_argument &e) {
        throw ParseException("Invalid Json, '" + str + "' is not valid.");
    }
}
