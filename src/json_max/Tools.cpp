/**
 * @author Max Van Houcke
 */

#include <fstream>
#include <sstream>
#include "Tools.h"
#include "Exceptions.h"

using namespace JsonMax;

std::string Tools::indent(const std::string &json, int indentation) {
    std::string output;
    unsigned int spaces = 0;
    bool escape = false;
    bool inString = false;

    for (size_t i = 0; i < json.size(); i++) {
        char symbol = json[i];

        // Two special cases, escaped symbol or in string
        if (escape) {
            output += symbol;
            escape = false;
            continue;
        } else if (inString) {
            inString = '"' != symbol;
            output += symbol;
            continue;
        }

        // Non empty object or array started
        if ((symbol == '{' and json[i + 1] != '}') or (symbol == '[' and json[i + 1] != ']')) {
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        }
        // Non empty object or array ended
        else if ((symbol == '}' and json[i - 1] != '{') or (symbol == ']' and json[i - 1] != '[')) {
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        }
        // Comma so new line and indent
        else if (symbol == ',') {
            output += ",\n" + std::string(spaces - 1, ' ');
        }
        // Other symbols
        else {
            // Check if escape or string started
            if (symbol == '\\') {
                escape = true;
            } else if (symbol == '"') {
                inString = true;
            }
            output += symbol;
        }
    }

    return output;
}

std::string Tools::doubleToString(const double &dou) {
    std::string str = std::to_string(dou);
    if (str.find('.') != std::string::npos) {
        while (str.back() == '0' and str[str.length() - 2] != '.') {
            str.pop_back();
        }
    }
    return str;
}


std::string Tools::fileToString(const std::string &fileName) {
    std::ifstream in(fileName);
    if (not in.good()) {
        throw ParseException("Couldn't open " + fileName);
    }
    std::ostringstream stream;
    stream << in.rdbuf();
    return stream.str();
}
