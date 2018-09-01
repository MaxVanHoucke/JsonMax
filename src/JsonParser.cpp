/**
 * @author Max Van Houcke
 */

#include "../include/JsonParser.h"

JsonElement JsonParser::parse(const std::string &json) {

    JsonElement output;

    bool inString = false;
    bool skip = false;
    bool inArray = false;
    bool inObject = false;

    std::string element;

    for (int i = 0; i < element.size(); i++) {
        char symbol = json[i];



//        if (symbol == '\\') {
//            skip = true;
//            continue;
//        }
//        else if (symbol == '\"') {
//            inString = !inString;
//        }
//        else if (symbol == '{') {
//
//        }
//
//
//        skip = false;
    }

}

int JsonParser::findIndex(int start, char symbol, const std::string &string) {
    bool skip = false;

    for (int i = start; i < string.size(); i++) {
        if (skip) {
            skip = false;
            continue;
        }

        if (string[i] == '\\') {
            skip = true;
            continue;
        }

        if (string[i] == symbol) {
            return i;
        }
    }

    return -1;
}

bool JsonParser::validateNumber(const std::string &number) {
    unsigned int index = 0;
    bool valid = false;

    try
    {
        if (number.at(0) == '-') {
            index++;
        }

        if (number.at(index) == '0') {
            index++;
            goto point;
        }
        else if (isdigit(number.at(index))) {
            valid = true;
            while (isdigit(number.at(index))) {
                index++;
            }
        }
        else return false;

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
        }
        else return false;

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
    catch (std::out_of_range& exception) {
        return valid;
    }
}

bool JsonParser::validateString(const std::string &string) {
    bool escape = false;

    for (int i = 0; i < string.size(); i++) {
        char symbol = string[i];

        if (escape) {

            if (!(symbol == '"' or symbol == '\\'
                  or symbol == '/' or symbol == 'b'
                  or symbol == 'f' or symbol == 'n'
                  or symbol == 'r' or symbol == 't'
                  or symbol == 'u')) return false;

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
        }
        else if (symbol == '\\') escape = true;
        else if (symbol == '\"') return false;
    }
    return true;
}