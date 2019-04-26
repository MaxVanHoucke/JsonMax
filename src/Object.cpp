/**
 * @author Max Van Houcke
 */

#include "../include/Object.h"
#include "../include/Element.h"
#include "../include/Tools.h"
#include "../include/Pair.h"

using namespace JsonMax;

Object::Object(JsonMax::Storage _storage): storage(_storage) {
    switch (storage) {
        case HASHMAP: 
            data.elementsHashmap = new std::unordered_map<std::string, Element>();
            break;
        case MAP:
            data.elementsMap = new std::map<std::string, Element>();
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
            data.elementsHashmap = new std::unordered_map<std::string, Element>(*obj.data.elementsHashmap);
            break;
        case MAP:
            data.elementsMap = new std::map<std::string, Element>(*obj.data.elementsMap);
            break;
        case VECTOR:
            data.elementsVector = new std::vector<std::pair<std::string, Element>>(*obj.data.elementsVector);
            break;
    }
}

Object::Object(JsonMax::Object &&obj) noexcept {
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

Object& Object::operator=(JsonMax::Object &&obj) noexcept {
    if (&obj != this) {
        reset();
        move(std::move(obj));
    }
    return *this;
}


Element &Object::operator[](const std::string &member) {
    if (storage == VECTOR) {
        for (auto &elem: *data.elementsVector) {
            if (elem.first == member) {
                return elem.second;
            }
        }
        data.elementsVector->emplace_back(member, Element());
        return data.elementsVector->back().second;
    } else if (storage == MAP) {
        for (auto &elem: *data.elementsMap) {
            if (elem.first == member) {
                return elem.second;
            }
        }
        data.elementsMap->emplace(member, Element());
        return data.elementsMap->operator[](member);
    } else if (storage == HASHMAP) {
        for (auto &elem: *data.elementsHashmap) {
            if (elem.first == member) {
                return elem.second;
            }
        }
        data.elementsHashmap->emplace(member, Element());
        return data.elementsHashmap->operator[](member);
    }
}

std::string Object::toString(unsigned int ind) const {
    std::string output = "{";
    if (storage == VECTOR) {
        for (auto &elem: *data.elementsVector) {
            if (elem.second.getType() == Type::UNINITIALIZED) {
                continue;
            }
            output += "\"" + elem.first + "\": " + elem.second.toString(0) + ", ";
        }
    } else if (storage == MAP) {
        for (auto &elem: *data.elementsMap) {
            if (elem.second.getType() == Type::UNINITIALIZED) {
                continue;
            }
            output += "\"" + elem.first + "\": " + elem.second.toString(0) + ", ";
        }
    } else if (storage == HASHMAP) {
        for (auto &elem: *data.elementsHashmap) {
            if (elem.second.getType() == Type::UNINITIALIZED) {
                continue;
            }
            output += "\"" + elem.first + "\": " + elem.second.toString(0) + ", ";
        }
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
    if (storage == VECTOR) {
        for (auto itr = data.elementsVector->begin(); itr != data.elementsVector->end(); ++itr) {
            if (itr->first == key) {
                data.elementsVector->erase(itr);
                break;
            }
        }
    } else if (storage == MAP) {
        data.elementsMap->erase(key);
    } else if (storage == HASHMAP) {
        data.elementsHashmap->erase(key);
    }
}


std::vector<Pair> Object::pairs() const {
    std::vector<Pair> pairs;
    if (storage == VECTOR) {
        for (auto &elem: *data.elementsVector) {
            if (elem.second.getType() != Type::UNINITIALIZED) {
                pairs.emplace_back(elem.first, elem.second);
            }
        }
    } else if (storage == MAP) {
        for (auto &elem: *data.elementsMap) {
            if (elem.second.getType() != Type::UNINITIALIZED) {
                pairs.emplace_back(elem.first, elem.second);
            }
        }
    } else if (storage == HASHMAP) {
        for (auto &elem: *data.elementsHashmap) {
            if (elem.second.getType() != Type::UNINITIALIZED) {
                pairs.emplace_back(elem.first, elem.second);
            }
        }
    }
    return pairs;
}

size_t Object::size() const {
    if (storage == VECTOR) {
        return data.elementsVector->size();
    } else if (storage == MAP) {
        return data.elementsMap->size();
    } else if (storage == HASHMAP) {
        return data.elementsHashmap->size();
    }
    return 0;
}

bool Object::exists(const std::string &key) const {
    if (storage == VECTOR) {
        for (auto& element: *data.elementsVector) {
            if (element.first == key && element.second.getType() != UNINITIALIZED) {
                return true;
            }
        }
        return false;
    } else if (storage == MAP) {
        return data.elementsMap->count(key) && data.elementsMap->operator[](key).getType() != UNINITIALIZED;
    } else if (storage == HASHMAP) {
        return data.elementsHashmap->count(key) && data.elementsHashmap->operator[](key).getType() != UNINITIALIZED;
    }
    return false;
}

bool Object::empty() const {
    if (storage == VECTOR) {
        for (auto& element: *data.elementsVector) {
            if (element.second.getType() != UNINITIALIZED) {
                return false;
            }
        }
        return true;
    } else if (storage == MAP) {
        for (auto& element: *data.elementsMap) {
            if (element.second.getType() != UNINITIALIZED) {
                return false;
            }
        }
        return true;
    } else if (storage == HASHMAP) {
        for (auto& element: *data.elementsHashmap) {
            if (element.second.getType() != UNINITIALIZED) {
                return false;
            }
        }
        return true;
    }
    return true;
}

void Object::clear() {
    if (storage == VECTOR) {
        data.elementsVector->clear();
    } else if (storage == MAP) {
        data.elementsMap->clear();
    } else if (storage == HASHMAP) {
        data.elementsHashmap->clear();
    }
}
