/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONOBJECT_H
#define JSONMAX_JSONOBJECT_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class JsonElement;

class Object {
public:

    /**
     * Constructor
     */
    Object() = default;

    /**
     * @param member
     * @return
     */
    JsonElement &operator[](const std::string &member);

    std::string toString(unsigned int indent = 0) const;

    static std::string indent(const std::string &json, int indentation);

private:

    /**
     * The elements of the object
     */
    std::vector<std::pair<std::string, JsonElement *>> elements;

};

#endif //JSONMAX_JSONOBJECT_H
