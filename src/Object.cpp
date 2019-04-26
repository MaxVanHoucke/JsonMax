/**
 * @author Max Van Houcke
 */

#include "../include/Object.h"
#include "../include/Element.h"
#include "../include/Tools.h"

using namespace JsonMax;

Object::Object(JsonMax::Object::Storage _storage): storage(_storage) {
    switch (storage) {
        case HASHMAP: 
            data.elementsHashmap = new std::unordered_map<std::string, Element*>();
            break;
        case MAP:
            data.elementsMap = new std::map<std::string, Element*>();
            break;
        case VECTOR:
            data.elementsVector = new std::vector<std::pair<std::string, Element>>();
            break;
    }
}

Object::~Object() {
    reset();
}


void Object::reset() {
    switch (storage) {
        case HASHMAP:
            delete data.elementsHashmap;
            break;
        case MAP:
            delete data.elementsMap;
            break;
        case VECTOR:
            delete data.elementsVector;
            break;
    }
}


void Object::move(JsonMax::Object &&obj) {
    storage = obj.storage;
    switch (obj.storage) {
        case HASHMAP:
            data.elementsHashmap = obj.data.elementsHashmap;
            obj.data.elementsHashmap = nullptr;
            break;
        case MAP:
            data.elementsMap = obj.data.elementsMap;
            obj.data.elementsMap = nullptr;
            break;
        case VECTOR:
            data.elementsVector = obj.data.elementsVector;
            obj.data.elementsVector = nullptr;
            break;
    }
}

void Object::copy(const JsonMax::Object &obj) {
    storage = obj.storage;
    switch (obj.storage) {
        case HASHMAP:
            data.elementsHashmap = new std::unordered_map<std::string, Element*>(*obj.data.elementsHashmap);
            break;
        case MAP:
            data.elementsMap = new std::map<std::string, Element*>(*obj.data.elementsMap);
            break;
        case VECTOR:
            data.elementsVector = new std::vector<std::pair<std::string, Element>>(*obj.data.elementsVector);
            break;
    }
}

Object::Object(JsonMax::Object &&obj) {
    move(std::move(obj));
}


Object::Object(const JsonMax::Object &obj) {
    copy(obj);
}

Object& Object::operator=(const JsonMax::Object &obj) {
    if (&obj != this) {
        reset();
        copy(obj);
    }
    return *this;
}

Object& Object::operator=(JsonMax::Object &&obj) {
    if (&obj != this) {
        reset();
        move(std::move(obj));
    }
    return *this;
}


Element &Object::operator[](const std::string &member) {
    for (auto &elem: *data.elementsVector) {
        if (elem.first == member) {
            return elem.second;
        }
    }
    data.elementsVector->emplace_back(member, Element());
    return data.elementsVector->back().second;
}

std::string Object::toString(unsigned int ind) const {
    std::string output = "{";
    for (const auto &elem: *data.elementsVector) {
        if (elem.second.getType() == Type::UNINITIALIZED) {
            continue;
        }
        output += "\"" + elem.first + "\": " + elem.second.toString(0) + ", ";
    }
    if (output.size() > 2) {
        output.pop_back();
        output.pop_back();
    }
    output += "}";

    if (ind) {
        return Tools::indent(output, ind);
    }

    return output;
}


void Object::remove(const std::string &key) {

}
