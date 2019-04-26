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
            return std::to_string(*data.number);
        case BOOLEAN:
            if (data.boolean) return "true";
            else return "false";
        case FRACTION:
            return std::to_string(*data.fraction);
        case OBJECT:
            return data.object->toString(ind);
        case STRING:
            return "\"" + *data.string + "\"";
        case ARRAY: {
            std::string arrayElements = "[";
            for (size_t i = 0; i < data.array->size(); i++) {
                arrayElements += data.array->at(i).toString();
                if (i != data.array->size() - 1) arrayElements += ", ";
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
    reset();
    setNumber(num);
    return *this;
}

Element &Element::operator=(double fraction) {
    reset();
    setFraction(fraction);
    return *this;
}

Element &Element::operator=(const Object &obj) {
    reset();
    setObject(obj);
    return *this;
}

Element &Element::operator=(const std::string &string) {
    reset();
    setString(string);
    return *this;
}

Element &Element::operator=(const std::vector<Element> &arr) {
    reset();
    setArray(arr);
    return *this;
}

Element &Element::operator=(bool boolean) {
    reset();
    setBoolean(boolean);
    return *this;
}

Element &Element::operator=(const char *c_string) {
    reset();
    setString(c_string);
    return *this;
}

Element& Element::operator[](const std::string &str) {
    if (type == OBJECT) {
        return data.object->operator[](str);
    }
    throw TypeException("Invalid use of operator[](const char*), element is not a json object.");
}

void Element::setNumber(int number) {
    Element::data.number = new int(number);
    type = INTEGER;
}

void Element::setBoolean(bool boolean) {
    Element::data.boolean = boolean;
    type = BOOLEAN;
}

void Element::setFraction(double fraction) {
    Element::data.fraction = new double(fraction);
    type = FRACTION;
}

void Element::setObject(const Object& object) {
    Element::data.object = new Object(object);
    type = OBJECT;
}

void Element::setString(const std::__cxx11::basic_string<char> &string) {
    Element::data.string = new std::string(string);
    type = STRING;
}

void Element::setArray(const std::vector<Element> &array) {
    Element::data.array = new std::vector<Element>(array);
    type = ARRAY;
}

int Element::getInt() const {
    checkType(INTEGER);
    return *data.number;
}

double Element::getDouble() const {
    checkType(FRACTION);
    return *data.fraction;
}

std::string& Element::getString() const {
    checkType(STRING);
    return *data.string;
}

bool Element::getBool() const {
    checkType(BOOLEAN);
    return data.boolean;
}

Object& Element::getObject() const {
    checkType(OBJECT);
    return *data.object;
}

Array& Element::getArray() const {
    checkType(ARRAY);
    return *data.array;
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
    reset();
    if (pointer == nullptr) {
        type = JSON_NULL;
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
    reset();
    setArray(arr);
    return *this;
}

void Element::reset() {
    switch (type) {
        case INTEGER: delete data.number;
            break;
        case FRACTION: delete data.fraction;
            break;
        case OBJECT: delete data.object;
            break;
        case STRING: delete data.string;
            break;
        case ARRAY: delete data.array;
            break;
        default:
            break;
    }
    type = UNINITIALIZED;
}

Element::~Element() {
    reset();
}


void Element::copy(const JsonMax::Element &obj) {
    type = obj.type;
    switch (type) {
        case INTEGER: data.number = new int(*obj.data.number);
            break;
        case FRACTION: data.fraction = new double(*obj.data.fraction);
            break;
        case STRING: data.string = new std::string(*obj.data.string);
            break;
        case OBJECT: data.object = new Object(*obj.data.object);
            break;
        case ARRAY: data.array = new Array(*obj.data.array);
            break;
        case BOOLEAN: data.boolean = obj.data.boolean;
            break;
        default:
            break;
    }
}

void Element::move(JsonMax::Element &&obj) {
    type = obj.type;
    switch (type) {
        case INTEGER: data.number = obj.data.number;
            obj.data.number = nullptr;
            break;
        case FRACTION: data.fraction = obj.data.fraction;
            obj.data.fraction = nullptr;
            break;
        case STRING: data.string = obj.data.string;
            obj.data.string = nullptr;
            break;
        case OBJECT: data.object = obj.data.object;
            obj.data.object = nullptr;
            break;
        case ARRAY: data.array = obj.data.array;
            obj.data.array = nullptr;
            break;
        case BOOLEAN: data.boolean = obj.data.boolean;
            break;
        default:
            break;
    }
}


Element::Element(const JsonMax::Element &obj) {
    copy(obj);
}

Element::Element(JsonMax::Element &&obj) noexcept {
    move(std::move(obj));
}

Element& Element::operator=(JsonMax::Element &&obj) noexcept {
    if (this != &obj) {
        reset();
        move(std::move(obj));
    }
    return *this;
}

Element& Element::operator=(const JsonMax::Element &obj) {
    if (this != &obj) {
        reset();
        copy(obj);
    }
    return *this;
}
