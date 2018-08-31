/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONOBJECT_H
#define JSONMAX_JSONOBJECT_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "JsonElement.h"


class JsonObject {
public:

    /**
     * Constructor
     */
    JsonObject() = default;

    /**
     * @param member
     * @return
     */
    JsonElement& operator[](const std::string& member);

    std::string toString(int indent = 0) const;

    static std::string indent(const std::string& json, int indentation);

private:

    /**
     * The elements of the object
     */
    std::vector<std::pair<std::string, JsonElement*>> elements;

};

#endif //JSONMAX_JSONOBJECT_H
