/**
 * @author Max Van Houcke
 */

#include "../include/JsonParser.h"

JsonElement JsonParser::parse(const std::string &json) {
    std::string element = trim(json);

    if (element == "true") {
        return JsonElement(true);
    } else if (element == "false") {
        return JsonElement(false);
    } else if (element == "null") {
        return JsonElement(nullptr);
    }

    JsonElement output;

    if (element.empty()) {
        return JsonElement();
    }

    if (element[0] == '{') {
        if (element.back() != '}') {
            //EXCEPTION
        }
        return parseObject(element.substr(1, element.size() - 2));
    }

    if (element[0] == '[') {
        if (element.back() != ']') {
            //EXCEPTION
        }
        return parseArray(element.substr(1, element.size() - 2));
    }

    if (validateNumber(element)) {
        try {
            double number = std::stod(element);
            if (element.find('.') == std::string::npos) {
                return JsonElement((int) number);
            }
            else return JsonElement(number);
        } catch (std::out_of_range& e) {

        } catch (std::invalid_argument& e) {

        }
    }

    if (element[0] == '"') {
        if (element.back() != '"') {
            //EXCEPTION
        }
        if (!validateString(element.substr(1, element.size() - 2))) {
            //EXCEPTION
        }
        return JsonElement(element.substr(1, element.size() - 2));
    }

    //EXCEPTION
}

int JsonParser::findIndex(size_t start, char symbol, const std::string &string) {
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

std::string JsonParser::trim(const std::string &str) {
    const auto strBegin = str.find_first_not_of(" \t\n");
    if (strBegin == std::string::npos) return "";
    const auto strEnd = str.find_last_not_of(" \t\n");
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}


JsonElement JsonParser::parseArray(const std::string &array) {

}

JsonObject JsonParser::parseObject(const std::string &object) {
    std::string element = trim(object);

    if (element.empty()) {
        return JsonObject();
    }

    JsonObject json;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);
        if (index == std::string::npos or element[index] != '"') {
            std::cout << "Exception";
        }

        int i = findIndex(index + 1, '"', element);
        if (i == -1) {
            std::cout << "Exception";
        }

        std::string key = element.substr(index + 1, i - index - 1);

        if (json[key].getType() != JsonElement::UNINITIALIZED) {
            std::cout << "Exception";
        }

        index = size_t(i) + 1;

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos or element[index] != ':') {
            std::cout << "Exception";
        }

        index++;

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            std::cout << "Exception";
        }

        if (element[index] == '{') {
            int i = findEnding(index, '{', element);
            if (i == -1) {
                std::cout << "Exception";
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        }

        else if (element[index] == '[') {
            //TODO
        }

        else {
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
            std::cout << "Exception";
        }

        index++;

    }

    return json;
}

int JsonParser::findEnding(size_t start, char symbol, const std::string& string) {
    bool skip = false;
    bool inString = false;

    char endSymbol;
    if (symbol == '{') {
        endSymbol = '}';
    } else if (symbol == '[') {
        endSymbol = ']';
    }

    int endCount = 0;
    int startCount = 0;

    for (int i = start; i < string.size(); i++) {
        char sym = string[i];

        if (skip) {
            skip = false;
            continue;
        }

        if (sym == '\\') {
            skip = true;
            continue;
        }
        else if (sym == '"') {
            inString = !inString;
        }
        else if (sym == symbol and !inString) {
            startCount++;
        }
        else if (sym == endSymbol and !inString) {
            endCount++;

            if (startCount == endCount) {
                return i;
            }
        }
    }
    return -1;
}
