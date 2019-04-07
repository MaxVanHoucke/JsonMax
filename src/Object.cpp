/**
 * @author Max Van Houcke
 */

#include "../include/Object.h"
#include "../include/JsonElement.h"
#include "../include/Tools.h"

using namespace JsonMax;

JsonElement &Object::operator[](const std::string &member) {
    for (const auto &elem: elements) {
        if (elem.first == member) {
            return *elem.second;
        }
    }
    auto element = new JsonElement();
    elements.emplace_back(member, element);
    return *element;
}

std::string Object::toString(unsigned int ind) const {
    std::string output = "{";
    for (const auto &elem: elements) {
        if (elem.second->getType() == Type::UNINITIALIZED) {
            continue;
        }
        output += "\"" + elem.first + "\": " + elem.second->toString(0) + ", ";
    }
    if (output.size() > 2) {
        output.pop_back();
        output.pop_back();
    }
    output += "}";

    if (ind) {
        return Tools::indent(output, ind);
    }

    return output;
}

