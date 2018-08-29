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
     *
     * @param member
     * @return
     */
    JsonElement operator[](const std::string& member);

private:

    /**
     * The elements of the object
     */
    std::unordered_map<std::string, JsonElement> elements;

};

#endif //JSONMAX_JSONOBJECT_H
