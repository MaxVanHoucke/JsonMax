/**
 * @author Max Van Houcke
 */

#include "Parser.h"
#include "../Exceptions.h"

#include <fstream>
#include <sstream>

using namespace JsonMax;

Element JsonMax::parse(const std::string &json) {
    std::string element = Parser::trim(json);

    if (element.empty()) {
        return Element();
    } else if (element == "true") {
        return Element(true);
    } else if (element == "false") {
        return Element(false);
    } else if (element == "null") {
        return Element(nullptr);
    } else if (element[0] == '{') {
        return Parser::parseObject(element);
    } else if (element[0] == '[') {
        return Parser::parseArray(element);
    } else if (element[0] == '"') {
        return Parser::parseString(element);
    } else {
        return Parser::parseNumber(element);
    }

    throw ParseException("Invalid Json, element " + element + " is not a supported type.");
}


Element Parser::parseArrayContent(const std::string &array) {
    return ObjectParser(array).parseArray();
}

Element ObjectParser::parse() {
    Element obj = Object();
    while (not endOfParsing()) {
        std::string key = extractKeyAndAdjustIndex();
        checkForDoublePointAndAdjustIndex();
        std::string element = extractElementAndAdjustIndex();
        obj[key] = JsonMax::parse(element);
    }
    return obj;
}

Element ObjectParser::parseArray() {
    Array array;
    while (not endOfParsing()) {
        std::string element = extractElementAndAdjustIndex();
        array.push_back(JsonMax::parse(element));
    }
    return Element(array);
}

bool ObjectParser::endOfParsing() const {
    return index == std::string::npos or index >= json.size();
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
    index = findIndexOfCharAfterElement('"');
    if (endOfParsing()) {
        throw ParseException("Invalid Json, key in object has no ending");
    }
    index++;

    return json.substr(keyStart, index - keyStart - 1);
}

void ObjectParser::moveToNonEmptyPosition() {
    index = json.find_first_not_of(" \t\n", index);
}

void ObjectParser::checkForDoublePointAndAdjustIndex() {
    moveToNonEmptyPosition();
    if (endOfParsing() or json[index] != ':') {
        throw ParseException("Invalid Json, no ':' between key and value");
    }
    index++;
}

std::string ObjectParser::extractElementAndAdjustIndex() {
    moveToNonEmptyPosition();
    size_t indexOfNextComma = findIndexOfCharAfterElement(',');
    std::string element = json.substr(index, indexOfNextComma - index);
    if (indexOfNextComma == std::string::npos) {
        index = std::string::npos;
    } else {
        index = indexOfNextComma + 1;
    }
    return element;
}


Object Parser::parseObjectContent(const std::string &object) {
    return ObjectParser(object).parse().getObject();
}


Element Parser::parseString(const std::string &string) {
    if (Parser::isValidString(string)) {
        std::string jsonStringWithoutQuotations = string.substr(1, string.size() - 2);
        return Element(jsonStringWithoutQuotations);
    }
    throw ParseException("Invalid Json, string " + string + " is invalid as per Json rules.");
}


Element Parser::parseNumber(const std::string &element) {
    try {
        return parseNumberFromString(element);
    } catch (std::out_of_range &e) {
        throw ParseException("Cannot parse, number '" + element + "' is out of range.");
    } catch (std::invalid_argument &e) {
        throw ParseException("Invalid Json, number '" + element + "' is not valid.");
    }
}

Element Parser::parseNumberFromString(const std::string &element) {
    double number = std::stod(element);
    if (element.find('.') == std::string::npos) {
        return Element((int) number);
    } else {
        return Element(number);
    }
}


std::string Parser::fileToString(const std::string &fileName) {
    std::ifstream in(fileName);
    if (not in.good()) {
        throw ParseException("Couldn't open " + fileName);
    }
    std::ostringstream stream;
    stream << in.rdbuf();
    return stream.str();
}


Element JsonMax::parseFile(const std::string &fileName) {
    std::string fileContent = Parser::fileToString(fileName);
    return parse(fileContent);
}

bool Parser::isValidString(const std::string &input) {
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

bool JsonMax::escapedHexadecimalIsCorrect(const std::string& input, size_t index) {
    if (index + 4 >= input.size()) {
        return false;
    }
    const static std::string hexa = "0123456789abcdefABCDEF";
    size_t result = input.find_first_not_of(hexa.c_str(), index + 1, 4);
    return result != std::string::npos;
}


bool JsonMax::escapedStringPartIsValid(const std::string& input, size_t index) {
    char symbol = input[index];
    // Allowed chars after escape
    const static std::string allowed = "\"\\/bfnrtu";
    if (allowed.find(symbol) == std::string::npos) {
        return false;
    }
    // u has to be followed by 4 hexadecimal units
    return symbol != 'u' or escapedHexadecimalIsCorrect(input, index);
}


std::string Parser::trim(const std::string &str) {
    const auto strBegin = str.find_first_not_of(" \t\n");
    if (strBegin == std::string::npos) return "";
    const auto strEnd = str.find_last_not_of(" \t\n");
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

Element Parser::parseArray(const std::string &array) {
    if (array.back() != ']') {
        throw ParseException("Invalid Json: array does not end with '}'");
    }
    return Parser::parseArrayContent(array.substr(1, array.size() - 2));
}

Object Parser::parseObject(const std::string &object) {
    if (object.back() != '}') {
        throw ParseException("Invalid Json: object does not end with '}'");
    }
    return Parser::parseObjectContent(object.substr(1, object.size() - 2));
}


size_t ObjectParser::findIndexOfCharAfterElement(char symbol) {
    bool skip = false;
    bool inString = false;

    int arrayCounter = 0;
    int objectCounter = 0;
    for (size_t i = index; i < json.size(); i++) {
        char current = json[i];

        if (skip) {
            skip = false;
            continue;
        } else if (inString) {
            inString = current != '"';
            continue;
        }

        if (current == symbol and objectCounter == 0 and arrayCounter == 0) {
            return i;
        }

        if (current == '\\') {
            skip = true;
        } else if (current == '"') {
            inString = true;
        } else if (current == '{') {
            objectCounter++;
        } else if (current == '}') {
            objectCounter--;
        } else if (current == '[') {
            arrayCounter++;
        } else if (current == ']') {
            arrayCounter--;
        }
    }

    return -1;
}
