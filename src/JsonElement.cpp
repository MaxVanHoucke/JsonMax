/**
 * @author Max Van Houcke
 */

#include <math.h>
#include "../include/JsonElement.h"
#include "../include/JsonObject.h"

JsonElement::JsonElement(): type(UNINITIALIZED) {}

std::string JsonElement::toString(unsigned int indent) const {
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
            std::string arrayElements = "[";
            for (int i = 0; i < array.size(); i++) {
                arrayElements += array[i].toString(indent);
                if (i != array.size() - 1) arrayElements += ", ";
            }
            arrayElements += "]";
            if (indent) JsonObject::indent(arrayElements, indent);
            return arrayElements;
        }
        case JSON_NULL:
            return "null";
        case UNINITIALIZED:
            return "UNINITIALIZED";
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

JsonElement& JsonElement::operator=(const JsonObject& obj) {
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

JsonElement& JsonElement::operator[](const char *c_string) {
    return object->operator[](c_string);
}


void JsonElement::setNumber(int number) {
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

void JsonElement::setNULL() {
    type = JSON_NULL;
}

JsonElement::operator int() const {
    checkType(INTEGER);
    return number;
}

JsonElement::operator double() const {
    checkType(FRACTION);
    return fraction;
}

JsonElement::operator std::string() const {
    checkType(STRING);
    return string;
}

JsonElement::operator const char*() const {
    checkType(STRING);
    return string.c_str();
}

JsonElement::operator bool() const {
    checkType(BOOLEAN);
    return boolean;
}

JsonElement::operator JsonObject() const {
    checkType(OBJECT);
    return JsonObject() = *object;
}

JsonElement::operator std::vector<JsonElement>() const {
    checkType(ARRAY);
    return array;
}

JsonElement::Type JsonElement::getType() const {
    return type;
}

void JsonElement::checkType(JsonElement::Type castType) const {
    if (type != castType) {
        throw TypeException(type, castType);
    }
}

JsonElement::JsonElement(const std::string &string) {
    setString(string);
}

JsonElement::JsonElement(const char *c_string) {
    setString(c_string);
}

JsonElement::JsonElement(int num) {
    setNumber(num);
}

JsonElement::JsonElement(double fract) {
    setFraction(fract);
}

JsonElement::JsonElement(bool boolean) {
    setBoolean(boolean);
}

JsonElement::JsonElement(const JsonObject &obj) {
    setObject(obj);
}

JsonElement::JsonElement(const std::vector<JsonElement> &arr) {
    setArray(arr);
}
