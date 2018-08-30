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

std::string JsonObject::toString() const {
    std::string output = "{";
    for (const auto& elem: elements) {
        output += "\"" + elem.first + "\": \"" + elem.second->toString(0) + "\", ";
    }
    output.pop_back();
    output.pop_back();
    output += "}";
    return output;
}