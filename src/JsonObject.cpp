/**
 * @author Max Van Houcke
 */

#include "../include/JsonObject.h"

JsonElement& JsonObject::operator[](const std::string &member) {
    for (const auto& elem: elements)
    {
        if (elem.first == member)
        {
            return *elem.second;
        }
    }
    auto element = new JsonElement();
    elements.emplace_back(member, element);
    return *element;
}

std::string JsonObject::toString(unsigned int indent) const {
    std::string output = "{";
    for (const auto &elem: elements) {
        if (elem.second->getType() == JsonElement::UNINITIALIZED) {
            continue;
        }
        output += "\"" + elem.first + "\": " + elem.second->toString(0) + ", ";
    }
    if (output.size() > 2) {
        output.pop_back();
        output.pop_back();
    }
    output += "}";

    if (indent) {
        return JsonObject::indent(output, indent);
    }

    return output;
}

std::string JsonObject::indent(const std::string &json, int indentation) {
    std::string output;
    unsigned int spaces = 0;
    bool escape = false;
    bool inString = false;

    for (char symbol: json) {
        bool normal = true;

        if (symbol == '\\') {
            output += symbol;
            escape = true;
            continue;
        } else if (symbol == '\"' and !escape) {
            inString = !inString;
        } else if ((symbol == '{' or symbol == '[') and !inString) {
            normal = false;
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        } else if ((symbol == '}' or symbol == ']') and !inString) {
            normal = false;
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        } else if (symbol == ',' and !inString) {
            output += ",\n" + std::string(spaces - 1, ' ');
            normal = false;
        }

        if (normal) {
            output += symbol;
        }

        escape = false;
    }

    return output;
}