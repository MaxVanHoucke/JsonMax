/**
 * @author Max Van Houcke
 */

#include <math.h>
#include "../include/JsonElement.h"
#include "../include/JsonObject.h"

JsonElement::JsonElement(): type(JSON_NULL) {}

std::string JsonElement::toString(int indent = 0) const {
    switch (type) {
        case INTEGER:
            return std::to_string(number);
        case BOOLEAN:
            if (boolean) return "true";
            else return "false";
        case FRACTION:
            return std::to_string(fraction);
        case OBJECT:
            return object->toString();
        case STRING:
            return "\"" + string + "\"";
        case ARRAY: {
            std::string arrayElements;
            for (int i = 0; i < array.size(); i++) {
                arrayElements += array[i].toString(indent);
                if (i != array.size() - 1) {
                    arrayElements += ", ";
                }
            }
            if (indent) {
                std::string returnVal = "[";
            }
            break;
        }
        case JSON_NULL:
            return "null";
    }
}


JsonElement& JsonElement::operator=(int num) {
    setNumber(num);
    return *this;
}

JsonElement& JsonElement::operator=(double fract) {
//    if (std::abs(std::round(fract) - fract) < )
    setFraction(fract);
    return *this;
}

JsonElement& JsonElement::operator=(JsonObject obj) {
    setObject(obj);
    return *this;
}

JsonElement& JsonElement::operator=(const std::string &string) {
    setString(string);
    return *this;
}

JsonElement& JsonElement::operator=(const std::vector<JsonElement> &arr) {
    setArray(arr);
    return *this;
}

JsonElement& JsonElement::operator=(bool boolean) {
    setBoolean(boolean);
    return *this;
}

JsonElement& JsonElement::operator=(const char *c_string) {
    setString(c_string);
    return *this;
}

JsonElement& JsonElement::operator[](const std::string &string) {
    return object->operator[](string);
}

JsonElement& JsonElement::operator[](const char *c_string) {
    return object->operator[](c_string);
}


void JsonElement::setNumber(long number) {
    JsonElement::number = number;
    type = INTEGER;
}

void JsonElement::setBoolean(bool boolean) {
    JsonElement::boolean = boolean;
    type = BOOLEAN;
}

void JsonElement::setFraction(double fraction) {
    JsonElement::fraction = fraction;
    type = FRACTION;
}

void JsonElement::setObject(JsonObject object) {
    JsonElement::object = new JsonObject();
    *JsonElement::object = object;
    type = OBJECT;
}

void JsonElement::setString(const std::__cxx11::basic_string<char> &string) {
    JsonElement::string = string;
    type = STRING;
}

void JsonElement::setArray(const std::vector<JsonElement> &array) {
    JsonElement::array = array;
    type = ARRAY;
}
