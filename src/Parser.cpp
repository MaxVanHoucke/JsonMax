/**
 * @author Max Van Houcke
 */

#include "Parser.h"
#include "Exceptions.h"

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
    } else if (Parser::isValidNumber(element)) {
        return Parser::parseNumber(element);
    }

    throw ParseException("Invalid Json, element " + element + " is not a supported type.");
}


Element Parser::parseArrayContent(const std::string &array) {
    std::string element = trim(array);

    if (element.empty()) {
        return Element(std::vector<Element>());
    }

    std::vector<Element> jsonArray;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            break;
        }

        if (element[index] == '{') {
            int i = findObjectEnding(index, element);
            if (i == -1) {
                throw ParseException("Invalid Json: object does not end with '}'");
            }

            jsonArray.push_back(parse(element.substr(index, i - index + 1)));
            index = i + 1;
        } else if (element[index] == '[') {
            int i = findArrayEnding(index, element);
            if (i == -1) {
                throw ParseException("Invalid Json: array does not end with ']'");
            }

            jsonArray.push_back(parse(element.substr(index, i - index + 1)));
            index = i + 1;
        } else {
            int a = findIndex(index, ',', element);
            if (a == -1) {
                a = element.size();
            }

            jsonArray.push_back(parse(element.substr(index, a - index)));
            index = size_t(a);
        }

        index = element.find_first_not_of(" ", index);

        if (index == std::string::npos) {
            break;
        }
        if (element[index] != ',') {
            throw ParseException("Invalid Json: invalid characters after value");
        }

        index++;
    }

    return Element(jsonArray);
}

Object Parser::parseObjectContent(const std::string &object) {
    std::string element = trim(object);

    if (element.empty()) {
        return Object();
    }

    Object json;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);
        if (index == std::string::npos or element[index] != '"') {
            throw ParseException("Invalid Json, key in object missing");
        }

        int i = findIndex(index + 1, '"', element);
        if (i == -1) {
            throw ParseException("Invalid Json, key in object has no ending");
        }

        std::string key = element.substr(index + 1, i - index - 1);

        index = size_t(i) + 1;
        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos or element[index] != ':') {
            throw ParseException("Invalid Json, no ':' between key and value");
        }

        index++;

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            throw ParseException("Invalid Json, key without value.");
        }

        if (element[index] == '{') {
            int i = findObjectEnding(index, element);
            if (i == -1) {
                throw ParseException("Invalid Json: object does not end with '}'");
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        } else if (element[index] == '[') {
            int i = findArrayEnding(index, element);
            if (i == -1) {
                throw ParseException("Invalid Json: array does not end with ']'");
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        } else {
            int a = findIndex(index, ',', element);
            if (a == -1) {
                a = element.size();
            }


            json[key] = parse(element.substr(index, a - index));
            index = size_t(a);
        }

        index = element.find_first_not_of(" ", index);

        if (index == std::string::npos) {
            break;
        }
        if (element[index] != ',') {
            throw ParseException("Invalid Json: invalid characters after value");
        }

        index++;
    }

    return json;
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


int Parser::findIndex(size_t start, char symbol, const std::string &string) {
    bool skip = false;
    bool inString = false;

    for (size_t i = start; i < string.size(); i++) {
        if (skip) {
            skip = false;
            continue;
        }

        if (string[i] == '\\') {
            skip = true;
            continue;
        } else if (string[i] == '"') {
            inString = !inString;
        }

        if (string[i] == symbol and (!inString or symbol == '"')) {
            return int(i);
        }
    }

    return -1;
}

bool Parser::isValidNumber(const std::string &number) {
    unsigned int index = 0;
    bool valid = false;

    try {
        if (number.at(0) == '-') {
            index++;
        }

        if (number.at(index) == '0') {
            index++;
            goto point;
        } else if (isdigit(number.at(index))) {
            valid = true;
            while (isdigit(number.at(index))) {
                index++;
            }
        } else return false;

        point:
        valid = true;

        if (number.at(index) == '.') {
            index++;
            valid = false;
            while (isdigit(number.at(index))) {
                valid = true;
                index++;
            }
        }

        if (number.at(index) == 'e' or number.at(index) == 'E') {
            index++;
            valid = false;
        } else return false;

        if (number.at(index) == '+' or number.at(index) == '-') {
            index++;
        }

        if (!isdigit(number.at(index))) {
            return false;
        }

        while (index != number.size()) {
            if (!isdigit(number.at(index))) {
                return false;
            }
            index++;
        }

        return true;
    }
    catch (std::out_of_range &exception) {
        return valid;
    }
}

bool Parser::isValidString(const std::string &input) {
    bool escape = false;
    if (input.size() < 2 or input[0] != '"' or input.back() != '"') {
        return false;
    }

    std::string string = input.substr(1, input.size() - 2);

    for (size_t i = 0; i < string.size(); i++) {
        char symbol = string[i];

        if (escape) {
            if (not(symbol == '"' or symbol == '\\'
                    or symbol == '/' or symbol == 'b'
                    or symbol == 'f' or symbol == 'n'
                    or symbol == 'r' or symbol == 't'
                    or symbol == 'u'))
                return false;

            if (symbol == 'u') {
                if (i + 4 >= string.size()) {
                    return false;
                }
                std::string hexa = string.substr(i + 1, 4);
                if (hexa.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos) {
                    return false;
                }
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


int Parser::findArrayEnding(size_t start, const std::string &string) {
    return findEnding(start, ']', string);
}

int Parser::findObjectEnding(size_t start, const std::string &string) {
    return findEnding(start, '}', string);
}

int Parser::findEnding(size_t start, char endSymbol, const std::string &string) {
    bool skip = false;
    bool inString = false;
    char startSymbol = endSymbol == ']' ? '[' : '{';
    int count = 0;

    for (size_t i = start; i < string.size(); i++) {
        char sym = string[i];

        if (skip) {
            skip = false;
            continue;
        } else if (inString) {
            inString = sym != '"';
            continue;
        }

        if (sym == '\\') {
            skip = true;
        } else if (sym == '"') {
            inString = true;
        } else if (sym == startSymbol) {
            count++;
        } else if (sym == endSymbol) {
            count--;

            if (count == 0) {
                return i;
            }
        }
    }

    return -1;
}
