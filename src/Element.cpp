/**
 * @author Max Van Houcke
 */

#include "../include/Element.h"
#include "../include/Object.h"
#include "../include/Exceptions.h"
#include "../include/Tools.h"

#include <math.h>

using namespace JsonMax;

Element::Element() : type(UNINITIALIZED) {}

std::string Element::toString(unsigned int ind) const {
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


Element &Element::operator=(int num) {
    setNumber(num);
    return *this;
}

Element &Element::operator=(double fraction) {
    setFraction(fraction);
    return *this;
}

Element &Element::operator=(const Object &obj) {
    setObject(obj);
    return *this;
}

Element &Element::operator=(const std::string &string) {
    setString(string);
    return *this;
}

Element &Element::operator=(const std::vector<Element> &arr) {
    setArray(arr);
    return *this;
}

Element &Element::operator=(bool boolean) {
    setBoolean(boolean);
    return *this;
}

Element &Element::operator=(const char *c_string) {
    setString(c_string);
    return *this;
}

Element &Element::operator[](const char *c_string) {
    if (type == OBJECT) {
        return object->operator[](c_string);
    }
    throw TypeException("Invalid use of operator[](const char*), element is not a json object.");
}

void Element::setNumber(int number) {
    Element::number = number;
    type = INTEGER;
}

void Element::setBoolean(bool boolean) {
    Element::boolean = boolean;
    type = BOOLEAN;
}

void Element::setFraction(double fraction) {
    Element::fraction = fraction;
    type = FRACTION;
}

void Element::setObject(Object object) {
    Element::object = new Object();
    *Element::object = object;
    type = OBJECT;
}

void Element::setString(const std::__cxx11::basic_string<char> &string) {
    Element::string = string;
    type = STRING;
}

void Element::setArray(const std::vector<Element> &array) {
    Element::array = array;
    type = ARRAY;
}

Element::operator int() const {
    checkType(INTEGER);
    return number;
}

Element::operator double() const {
    checkType(FRACTION);
    return fraction;
}

Element::operator std::string() const {
    checkType(STRING);
    return string;
}

Element::operator const char *() const {
    checkType(STRING);
    return string.c_str();
}

Element::operator bool() const {
    checkType(BOOLEAN);
    return boolean;
}

Element::operator Object() const {
    checkType(OBJECT);
    return Object() = *object;
}

Element::operator std::vector<Element>() const {
    checkType(ARRAY);
    return array;
}

Type Element::getType() const {
    return type;
}

void Element::checkType(Type castType) const {
    if (type != castType) {
        throw TypeException(type, castType);
    }
}

Element::Element(const std::string &string) {
    setString(string);
}

Element::Element(const char *c_string) {
    setString(c_string);
}

Element::Element(int num) {
    setNumber(num);
}

Element::Element(double fract) {
    setFraction(fract);
}

Element::Element(bool boolean) {
    setBoolean(boolean);
}

Element::Element(const Object &obj) {
    setObject(obj);
}

Element::Element(const std::vector<Element> &arr) {
    setArray(arr);
}

Element &Element::operator=(std::nullptr_t pointer) {
    if (pointer == nullptr) {
        type = JSON_NULL;
    } else {

    }
    return *this;
}

Element::Element(std::nullptr_t pointer) {
    if (pointer == nullptr) {
        type = JSON_NULL;
    }
}

Element::Element(const std::initializer_list<Element> &arr) {
    setArray(arr);
}

Element &Element::operator=(const std::initializer_list<Element> &arr) {
    setArray(arr);
}

Iterator Element::begin() {
    if (type == OBJECT) {
        return {0, object};
    }
    if (type == ARRAY) {
        return {0, &array};
    }

    throw TypeException("Can't iterate over " + toString(type));
}

Iterator Element::end() {
    if (type == OBJECT) {
        return {static_cast<int>(object->elements.size()), object};
    }
    if (type == ARRAY) {
        return {static_cast<int>(array.size()), &array};
    }

    throw TypeException("Can't iterate over " + toString(type));
}
