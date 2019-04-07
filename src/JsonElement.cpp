/**
 * @author Max Van Houcke
 */

#include "../include/JsonElement.h"
#include "../include/Object.h"
#include "../include/Exceptions.h"
#include "../include/Tools.h"

#include <math.h>

using namespace JsonMax;

JsonElement::JsonElement() : type(UNINITIALIZED) {}

std::string JsonElement::toString(unsigned int ind) const {
    switch (type) {
        case INTEGER:
            return std::to_string(number);
        case BOOLEAN:
            if (boolean) return "true";
            else return "false";
        case FRACTION:
            return std::to_string(fraction);
        case OBJECT:
            return object->toString(ind);
        case STRING:
            return "\"" + string + "\"";
        case ARRAY: {
            std::string arrayElements = "[";
            for (int i = 0; i < array.size(); i++) {
                arrayElements += array[i].toString();
                if (i != array.size() - 1) arrayElements += ", ";
            }
            arrayElements += "]";
            if (ind) return Tools::indent(arrayElements, ind);
            return arrayElements;
        }
        case JSON_NULL:
            return "null";
        case UNINITIALIZED:
            return "UNINITIALIZED";
    }
}


JsonElement &JsonElement::operator=(int num) {
    setNumber(num);
    return *this;
}

JsonElement &JsonElement::operator=(double fraction) {
    setFraction(fraction);
    return *this;
}

JsonElement &JsonElement::operator=(const Object &obj) {
    setObject(obj);
    return *this;
}

JsonElement &JsonElement::operator=(const std::string &string) {
    setString(string);
    return *this;
}

JsonElement &JsonElement::operator=(const std::vector<JsonElement> &arr) {
    setArray(arr);
    return *this;
}

JsonElement &JsonElement::operator=(bool boolean) {
    setBoolean(boolean);
    return *this;
}

JsonElement &JsonElement::operator=(const char *c_string) {
    setString(c_string);
    return *this;
}

JsonElement &JsonElement::operator[](const char *c_string) {
    if (type == OBJECT) {
        return object->operator[](c_string);
    }
    throw JsonTypeException("Invalid use of operator[](const char*), element is not a json object.");
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

void JsonElement::setObject(Object object) {
    JsonElement::object = new Object();
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

JsonElement::operator const char *() const {
    checkType(STRING);
    return string.c_str();
}

JsonElement::operator bool() const {
    checkType(BOOLEAN);
    return boolean;
}

JsonElement::operator Object() const {
    checkType(OBJECT);
    return Object() = *object;
}

JsonElement::operator std::vector<JsonElement>() const {
    checkType(ARRAY);
    return array;
}

Type JsonElement::getType() const {
    return type;
}

void JsonElement::checkType(Type castType) const {
    if (type != castType) {
        throw JsonTypeException(type, castType);
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

JsonElement::JsonElement(const Object &obj) {
    setObject(obj);
}

JsonElement::JsonElement(const std::vector<JsonElement> &arr) {
    setArray(arr);
}

JsonElement &JsonElement::operator=(std::nullptr_t pointer) {
    if (pointer == nullptr) {
        type = JSON_NULL;
    } else {

    }
    return *this;
}

JsonElement::JsonElement(std::nullptr_t pointer) {
    if (pointer == nullptr) {
        type = JSON_NULL;
    }
}

JsonElement::JsonElement(const std::initializer_list<JsonElement> &arr) {
    setArray(arr);
}

JsonElement &JsonElement::operator=(const std::initializer_list<JsonElement> &arr) {
    setArray(arr);
}

std::ostream &operator<<(std::ostream &out, const JsonElement &element) {
    std::string output = element.toString();
    if (!output.empty() and output.front() == '"' and output.back() == '"') {
        output.pop_back();
        if (!output.empty()) output.erase(0, 1);
    }
    out << output;
    return out;
}