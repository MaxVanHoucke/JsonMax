/**
 * @author Max Van Houcke
 */

#include "../include/Tools.h"

std::string JsonMax::Tools::indent(const std::string &json, int indentation) {
    std::string output;
    unsigned int spaces = 0;
    bool escape = false;
    bool inString = false;

    for (char symbol: json) {

        if (symbol == '\\' and !escape) {
            output += symbol;
            escape = true;
            continue;
        } else if (symbol == '\"' and !escape) {
            output += symbol;
            inString = !inString;
        } else if ((symbol == '{' or symbol == '[') and !inString) {
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        } else if ((symbol == '}' or symbol == ']') and !inString) {
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        } else if (symbol == ',' and !inString) {
            output += ",\n" + std::string(spaces - 1, ' ');
        } else output += symbol;

        escape = false;
    }

    return output;
}