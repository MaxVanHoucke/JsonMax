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
            return std::to_string(*storage.number);
        case BOOLEAN:
            if (storage.boolean) return "true";
            else return "false";
        case FRACTION:
            return std::to_string(*storage.fraction);
        case OBJECT:
            return storage.object->toString(ind);
        case STRING:
            return "\"" + *storage.string + "\"";
        case ARRAY: {
            std::string arrayElements = "[";
            for (size_t i = 0; i < storage.array->size(); i++) {
                arrayElements += storage.array->at(i).toString();
                if (i != storage.array->size() - 1) arrayElements += ", ";
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

Element &Element::operator[](const char *c_string) {
    if (type == OBJECT) {
        std::cout << "no pro" << std::endl;
        return storage.object->operator[](c_string);
    }
    throw TypeException("Invalid use of operator[](const char*), element is not a json object.");
}

Element& Element::operator[](const std::string &str) {
    return (*this)[str.c_str()];
}

void Element::setNumber(int number) {
    Element::storage.number = new int(number);
    type = INTEGER;
}

void Element::setBoolean(bool boolean) {
    Element::storage.boolean = boolean;
    type = BOOLEAN;
}

void Element::setFraction(double fraction) {
    Element::storage.fraction = new double(fraction);
    type = FRACTION;
}

void Element::setObject(const Object& object) {
    Element::storage.object = new Object(object);
    type = OBJECT;
}

void Element::setString(const std::__cxx11::basic_string<char> &string) {
    Element::storage.string = new std::string(string);
    type = STRING;
}

void Element::setArray(const std::vector<Element> &array) {
    Element::storage.array = new std::vector<Element>(array);
    type = ARRAY;
}

int Element::getInt() const {
    checkType(INTEGER);
    return *storage.number;
}

double Element::getDouble() const {
    checkType(FRACTION);
    return *storage.fraction;
}

std::string& Element::getString() const {
    checkType(STRING);
    return *storage.string;
}

bool Element::getBool() const {
    checkType(BOOLEAN);
    return storage.boolean;
}

Object& Element::getObject() const {
    checkType(OBJECT);
    return *storage.object;
}

Array& Element::getArray() const {
    checkType(ARRAY);
    return *storage.array;
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
        case INTEGER: delete storage.number;
            break;
        case FRACTION: delete storage.fraction;
            break;
        case OBJECT: delete storage.object;
            break;
        case STRING: delete storage.string;
            break;
        case ARRAY: delete storage.array;
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
        case INTEGER: storage.number = new int(*obj.storage.number);
            break;
        case FRACTION: storage.fraction = new double(*obj.storage.fraction);
            break;
        case STRING: storage.string = new std::string(*obj.storage.string);
            break;
        case OBJECT: storage.object = new Object(*obj.storage.object);
            break;
        case ARRAY: storage.array = new Array(*obj.storage.array);
            break;
        case BOOLEAN: storage.boolean = obj.storage.boolean;
            break;
        default:
            break;
    }
}

void Element::move(JsonMax::Element &&obj) {
    type = obj.type;
    switch (type) {
        case INTEGER: storage.number = obj.storage.number;
            obj.storage.number = nullptr;
            break;
        case FRACTION: storage.fraction = obj.storage.fraction;
            obj.storage.fraction = nullptr;
            break;
        case STRING: storage.string = obj.storage.string;
            obj.storage.string = nullptr;
            break;
        case OBJECT: storage.object = obj.storage.object;
            obj.storage.object = nullptr;
            break;
        case ARRAY: storage.array = obj.storage.array;
            obj.storage.array = nullptr;
            break;
        case BOOLEAN: storage.boolean = obj.storage.boolean;
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
