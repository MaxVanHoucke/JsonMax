/*
MIT License

Copyright (c) 2019 Max Van Houcke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef JSONMAX_H
#define JSONMAX_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <fstream>

namespace JsonMax {


    /// Forward declarations
    class Element;
    class Pair;

    /// Storage options for the Object
    enum Storage {
        HASHMAP,
        MAP,
        VECTOR
    };

    /// JSON Object representation
    class Object {
    public:

        /**
         * Constructor
         * Pick the storage type most suitable to your situation (see readme for more info)
         * @param storage the wanted storage type
         */
        explicit Object(Storage storage = HASHMAP);

        /**
         * Copy constructor
         * Deep copies all elements and uses the same storage type
         */
        Object(const Object&);

        /**
         * Move constructor
         * Moves the complete storage from the temp object
         */
        Object(Object&&) noexcept;

        /**
         * Copy assignment
         * Resets the current object
         * Deep copies all elements and uses the same storage type
         */
        Object& operator=(const Object&);

        /**
         * Move assignment
         * Resets the current object
         * Moves the complete storage from the temp object
         */
        Object& operator=(Object&&) noexcept;

        /**
         * Destructor
         * Cleans up resources
         */
        ~Object();

        /**
         * Fetches the Element with the given key
         * Creates a new one if not present
         * @param key str key of the object
         * @return element with the given key
         */
        Element &operator[](const std::string &key);

        /**
         * @param indent the wanted indentation (in spaces)
         * @return string representation of the object
         */
        std::string toString(unsigned int indent = 0) const;

        /**
         * Removes an item from the object
         * Does nothing when the object does not exist
         */
        void remove(const std::string&);

        /**
         * Fetches all pairs in the object
         * @return vector of pairs, easy to loop over
         */
        std::vector<Pair> pairs() const;

        /// @return amount of items in the object
        size_t size() const;

        /// @return true if the item with the given key exists
        bool exists(const std::string&) const;

        /// @return true if the object is empty
        bool empty() const;

        /// Clears all items from the object
        void clear();

    private:

        /// Cleans up resources
        void reset();

        /// Moves the given temp object to this
        void move(Object&&);

        /// Deep copies the given object to this
        void copy(const Object&);

        /// Union with pointer to the different kinds of storage types
        union Data {
            std::vector<std::pair<std::string, Element>>* elementsVector;
            std::map<std::string, Element>* elementsMap;
            std::unordered_map<std::string, Element>* elementsHashmap;
        };

        /// Actual data
        Data data;

        /// Storage type
        Storage storage;

    };



    /// Possible types of a JSON Element
    enum Type {
        INTEGER,
        BOOLEAN,
        FRACTION,
        OBJECT,
        STRING,
        ARRAY,
        JSON_NULL,
        UNINITIALIZED
    };

    /// Returns string representation of a type
    std::string toString(Type type);



    /// Forward declarations
    class Object;
    class Element;

    /// Name alias for a Json Array
    using Array = std::vector<Element>;

    /**
     * Representation of an Element in a JSON Object
     */
    class Element {
    public:

        /// Default constructor, sets type to uninitialized
        Element();

        /// Copy constructor
        Element(const Element&);

        /// Move constructor
        Element(Element&&) noexcept;

        /// Constructor for string
        Element(const std::string &string);

        /// Constructor for c string
        Element(const char *old_string);

        /// Constructor for int
        Element(int num);

        /// Constructor for double
        Element(double fraction);

        /// Constructor for boolean
        Element(bool boolean);

        /// Constructor for a JSON Object
        Element(const Object &obj);

        /// Constructor for a JSON Array
        Element(const Array &arr);

        /// Constructor for a JSON Array (initializer list)
        Element(const std::initializer_list<Element> &arr);

        /// Constructor for JSON null
        Element(std::nullptr_t pointer);

        /// Destructor, cleans up resources
        ~Element();

        /// Copy assignment
        Element& operator=(const Element&);

        /// Move assignment
        Element& operator=(Element&&) noexcept;

        /// String assignment
        Element &operator=(const std::string &string);

        /// C string assignment
        Element &operator=(const char *c_string);

        /// Int assignment
        Element &operator=(int num);

        /// Double assignment
        Element &operator=(double fract);

        /// Boolean assignment
        Element &operator=(bool boolean);

        /// JSON Object assignment
        Element &operator=(const Object &obj);

        /// JSON Array assignment
        Element &operator=(const Array &arr);

        /// JSON Array (initializer list) assignment
        Element &operator=(const std::initializer_list<Element> &arr);

        /// JSON null assignment
        Element &operator=(std::nullptr_t pointer);

        /// Getter for the current type
        Type getType() const;

        /// Returns the operator[] of the Object, throws exception if not an Object
        Element &operator[](const std::string&);

        /**
         * @param indent the wanted indentation (in spaces)
         * @return string representation of the object
         */
        std::string toString(unsigned int indent = 0) const;

        /// Int getter, throws type exception if wrong type
        int getInt() const;

        /// Boolean getter, throws type exception if wrong type
        bool getBool() const;

        /// Double getter, throws type exception if wrong type
        double getDouble() const;

        /// String getter, throws type exception if wrong type
        std::string& getString() const;

        /// Object getter, throws type exception if wrong type
        Object& getObject() const;

        /// Array getter, throws type exception if wrong type
        Array& getArray() const;
        
        /// Check if type is int
        bool isInt() const;

        /// Check if type is bool
        bool isBool() const;
        
        /// Check if type is double
        bool isDouble() const;

        /// Check if type is string
        bool isString() const;

        /// Check if type is JSON Object
        bool isObject() const;

        /// Check if type is JSON Array
        bool isArray() const;

        /// Check if type is JSON Null
        bool isNull() const;

    private:

        /// Moves the given temp object to this
        void move(Element&&);

        /// Deep copies the given object to this
        void copy(const Element&);

        /// Cleans up resources
        void reset();

        /// Throws a TypeException if the given type is not equal to the current one
        void checkType(Type castType) const;

        /// Makes the element an integer
        void setNumber(int number);

        /// Makes the element a boolean
        void setBoolean(bool boolean);

        /// Makes the element a fraction
        void setFraction(double fraction);

        /// Makes the element an object
        void setObject(const Object& object);

        /// Makes the element a string
        void setString(const std::string& string);

        /// Makes the element an array
        void setArray(const Array& array);

        /// Union with pointers to the different kinds of types
        union Data {
            int* number;
            bool boolean;
            double* fraction;
            Object* object;
            std::string* string;
            Array* array;
        };

        /// Actual data
        Data data;

        /// Element type
        Type type;

    };



    /// Pair in a JSON Object
    class Pair {
    public:

        /// Constructor with key and value
        Pair(std::string , Element);

        /// Getter for key
        const std::string &getKey() const;

        /// Getter vor value
        const Element &getValue() const;

    private:

        std::string key;
        Element value;

    };



    /**
     * Parses a given string into a json element (object, array, int,...)
     * @param json string
     * @return JSON Element, use appropriate getter to get the value
     */
    Element parse(const std::string& json);

    /**
     * @param fileName the name of the file
     * @return JSON Element parsed from file
     */
    Element parseFile(const std::string& fileName);

    /// Helper function for parsing
    namespace Parser {

        /// Finds the position of the next symbol given that is not in a json string
        int findIndex(size_t start, char symbol, const std::string &string);

        /// When giving '{' it finds the next '}' and returns the position
        int findEnding(size_t start, char symbol, const std::string &string);

        /// Checks if it's a valid json string
        bool validateString(const std::string &string);

        /// Checks if it's a valid json number
        bool validateNumber(const std::string &number);

        /// Trims the string, removes whitespace etc
        std::string trim(const std::string &string);

        /// Parses an object without the { and }
        Object parseObject(const std::string &object);

        /// Parses an array without the [ and ]
        Element parseArray(const std::string &array);

    }



    namespace Tools {

        /// Indents the given string with the given indentation (in spaces)
        std::string indent(const std::string &json, int indentation);

        /// Returns the string representation of a double, without any trailing zeroes after the comma
        std::string doubleToString(const double&);

    }




    class TypeException : public std::exception {
    public:

        friend class Element;

        virtual const char *what() const throw() {
            return msg.c_str();
        }

    protected:

        TypeException(Type actual, Type expected) {
            msg = "Casting an element of type " + toString(actual) + " to " +
                  toString(expected) + " is not possible.";
        }

        explicit TypeException(const std::string &str) {
            msg = str;
        }

        std::string msg;

    };


    class ParseException : public std::exception {
    public:

        friend Element parse(const std::string &);
        friend Element parseFile(const std::string &);
        friend Element Parser::parseArray(const std::string&);
        friend Object Parser::parseObject(const std::string&);

        virtual const char *what() const throw() {
            return msg.c_str();
        }

    protected:

        ParseException(const char *message) : msg(message) {}

        std::string msg;

    };



Element::Element() : type(UNINITIALIZED) {}

std::string Element::toString(unsigned int ind) const {
    switch (type) {
        case INTEGER:
            return std::to_string(*data.number);
        case BOOLEAN:
            if (data.boolean) return "true";
            else return "false";
        case FRACTION:
            return Tools::doubleToString(*data.fraction);
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

void Element::setString(const std::string &string) {
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


void Element::copy(const Element &obj) {
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

void Element::move(Element &&obj) {
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


Element::Element(const Element &obj) {
    copy(obj);
}

Element::Element(Element &&obj) noexcept {
    move(std::move(obj));
}

Element& Element::operator=(Element &&obj) noexcept {
    if (this != &obj) {
        reset();
        move(std::move(obj));
    }
    return *this;
}

Element& Element::operator=(const Element &obj) {
    if (this != &obj) {
        reset();
        copy(obj);
    }
    return *this;
}

bool Element::isInt() const {
    return type == INTEGER;
}

bool Element::isDouble() const {
    return type == FRACTION;
}

bool Element::isBool() const {
    return type == BOOLEAN;
}

bool Element::isObject() const {
    return type == OBJECT;
}

bool Element::isArray() const {
    return type == ARRAY;
}

bool Element::isString() const {
    return type == STRING;
}

bool Element::isNull() const {
    return type == JSON_NULL;
}


Pair::Pair(std::string str, Element ele): key(std::move(str)), value(std::move(ele)) {}

const std::string& Pair::getKey() const {
    return key;
}

const Element& Pair::getValue() const {
    return value;
}


Object::Object(Storage _storage): storage(_storage) {
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


void Object::move(Object &&obj) {
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

void Object::copy(const Object &obj) {
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

Object::Object(Object &&obj) noexcept {
    move(std::move(obj));
}


Object::Object(const Object &obj) {
    copy(obj);
}

Object& Object::operator=(const Object &obj) {
    if (&obj != this) {
        reset();
        copy(obj);
    }
    return *this;
}

Object& Object::operator=(Object &&obj) noexcept {
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


Element parse(const std::string &json) {
    std::string element = Parser::trim(json);

    if (element == "true") {
        return Element(true);
    } else if (element == "false") {
        return Element(false);
    } else if (element == "null") {
        return Element(nullptr);
    }

    Element output;

    if (element.empty()) {
        return Element();
    }

    if (element[0] == '{') {
        if (element.back() != '}') {
            throw ParseException("Invalid Json: object does not end with '}'");
        }
        return Parser::parseObject(element.substr(1, element.size() - 2));
    }

    if (element[0] == '[') {
        if (element.back() != ']') {
            throw ParseException("Invalid Json: array does not end with '}'");
        }
        return Parser::parseArray(element.substr(1, element.size() - 2));
    }

    if (Parser::validateNumber(element)) {
        try {
            double number = std::stod(element);
            if (element.find('.') == std::string::npos) {
                return Element((int) number);
            } else return Element(number);
        } catch (std::out_of_range &e) {
            throw ParseException(
                    std::string("Cannot parse, number '" + element + "' is out of range.").c_str());
        } catch (std::invalid_argument &e) {
            throw ParseException(std::string("Invalid Json, number '" + element + "' is not valid.").c_str());
        }
    }

    if (element[0] == '"') {
        if (element.back() != '"') {
            throw ParseException(std::string("Invalid Json, string " + element + " has no ending.").c_str());
        }
        if (!Parser::validateString(element.substr(1, element.size() - 2))) {
            throw ParseException(
                    std::string("Invalid Json, string " + element + " is invalid as per Json rules.").c_str());

        }
        return Element(element.substr(1, element.size() - 2));
    }

    throw ParseException(
            std::string("Invalid Json, element " + element + " is not a supported type.").c_str());
}


Element parseFile(const std::string &fileName) {
    std::ifstream in(fileName);

    if (not in.good()) {
        throw ParseException(std::string("Couldn't open " + fileName).c_str());
    }

    std::ostringstream stream;
    stream << in.rdbuf();

    return parse(stream.str());
}


int Parser::findIndex(size_t start, char symbol, const std::string &string) {
    bool skip = false;
    bool inString = false;

    for (size_t i = start; i < string.size(); i++) {
        if (skip) {
            skip = false;
            continue;
        }

        if (string[i] == '\\') {
            skip = true;
            continue;
        } else if (string[i] == '"') {
            inString = !inString;
        }

        if (string[i] == symbol and (!inString or symbol == '"')) {
            return int(i);
        }
    }

    return -1;
}

bool Parser::validateNumber(const std::string &number) {
    unsigned int index = 0;
    bool valid = false;

    try {
        if (number.at(0) == '-') {
            index++;
        }

        if (number.at(index) == '0') {
            index++;
            goto point;
        } else if (isdigit(number.at(index))) {
            valid = true;
            while (isdigit(number.at(index))) {
                index++;
            }
        } else return false;

        point:
        valid = true;

        if (number.at(index) == '.') {
            index++;
            valid = false;
            while (isdigit(number.at(index))) {
                valid = true;
                index++;
            }
        }

        if (number.at(index) == 'e' or number.at(index) == 'E') {
            index++;
            valid = false;
        } else return false;

        if (number.at(index) == '+' or number.at(index) == '-') {
            index++;
        }

        if (!isdigit(number.at(index))) {
            return false;
        }

        while (index != number.size()) {
            if (!isdigit(number.at(index))) {
                return false;
            }
            index++;
        }

        return true;
    }
    catch (std::out_of_range &exception) {
        return valid;
    }
}

bool Parser::validateString(const std::string &string) {
    bool escape = false;

    for (int i = 0; i < string.size(); i++) {
        char symbol = string[i];

        if (escape) {
            if (not(symbol == '"' or symbol == '\\'
                    or symbol == '/' or symbol == 'b'
                    or symbol == 'f' or symbol == 'n'
                    or symbol == 'r' or symbol == 't'
                    or symbol == 'u'))
                return false;

            if (symbol == 'u') {
                if (i + 4 >= string.size()) {
                    return false;
                }
                std::string hexa = string.substr(i + 1, 4);
                if (hexa.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos) {
                    return false;
                }
            }

            escape = false;
        } else if (symbol == '\\') {
            escape = true;
        } else if (symbol == '\"') {
            return false;
        }
    }
    return true;
}

std::string Parser::trim(const std::string &str) {
    const auto strBegin = str.find_first_not_of(" \t\n");
    if (strBegin == std::string::npos) return "";
    const auto strEnd = str.find_last_not_of(" \t\n");
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

Element Parser::parseArray(const std::string &array) {
    std::string element = trim(array);

    if (element.empty()) {
        return Element(std::vector<Element>());
    }

    std::vector<Element> jsonArray;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            break;
        }

        if (element[index] == '{') {
            int i = findEnding(index, '{', element);
            if (i == -1) {
                throw ParseException("Invalid Json: object does not end with '}'");
            }

            jsonArray.push_back(parse(element.substr(index, i - index + 1)));
            index = i + 1;
        } else if (element[index] == '[') {
            int i = findEnding(index, '[', element);
            if (i == -1) {
                throw ParseException("Invalid Json: array does not end with ']'");
            }

            jsonArray.push_back(parse(element.substr(index, i - index + 1)));
            index = i + 1;
        } else {
            int a = findIndex(index, ',', element);
            if (a == -1) {
                a = element.size();
            }

            jsonArray.push_back(parse(element.substr(index, a - index)));
            index = size_t(a);
        }

        index = element.find_first_not_of(" ", index);

        if (index == std::string::npos) {
            break;
        }
        if (element[index] != ',') {
            throw ParseException("Invalid Json: invalid characters after value");
        }

        index++;
    }

    return Element(jsonArray);
}

Object Parser::parseObject(const std::string &object) {
    std::string element = trim(object);

    if (element.empty()) {
        return Object();
    }

    Object json;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);
        if (index == std::string::npos or element[index] != '"') {
            throw ParseException(std::string("Invalid Json, key in object missing").c_str());
        }

        int i = findIndex(index + 1, '"', element);
        if (i == -1) {
            throw ParseException(std::string("Invalid Json, key in object has no ending").c_str());
        }

        std::string key = element.substr(index + 1, i - index - 1);

        index = size_t(i) + 1;
        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos or element[index] != ':') {
            throw ParseException(std::string("Invalid Json, no ':' between key and value").c_str());
        }

        index++;

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            throw ParseException(std::string("Invalid Json, key without value.").c_str());
        }

        if (element[index] == '{') {
            int i = findEnding(index, '{', element);
            if (i == -1) {
                throw ParseException("Invalid Json: object does not end with '}'");
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        } else if (element[index] == '[') {
            int i = findEnding(index, '[', element);
            if (i == -1) {
                throw ParseException("Invalid Json: array does not end with ']'");
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        } else {
            int a = findIndex(index, ',', element);
            if (a == -1) {
                a = element.size();
            }


            json[key] = parse(element.substr(index, a - index));
            index = size_t(a);
        }

        index = element.find_first_not_of(" ", index);

        if (index == std::string::npos) {
            break;
        }
        if (element[index] != ',') {
            throw ParseException("Invalid Json: invalid characters after value");
        }

        index++;
    }

    return json;
}


int Parser::findEnding(size_t start, char symbol, const std::string &string) {
    bool skip = false;
    bool inString = false;

    char endSymbol;
    if (symbol == '{') {
        endSymbol = '}';
    } else if (symbol == '[') {
        endSymbol = ']';
    }

    int endCount = 0;
    int startCount = 0;

    for (int i = start; i < string.size(); i++) {
        char sym = string[i];

        if (skip) {
            skip = false;
            continue;
        }

        if (sym == '\\') {
            skip = true;
            continue;
        } else if (sym == '"') {
            inString = !inString;
        } else if (sym == symbol and !inString) {
            startCount++;
        } else if (sym == endSymbol and !inString) {
            endCount++;

            if (startCount == endCount) {
                return i;
            }
        }
    }
    return -1;
}


std::string Tools::indent(const std::string &json, int indentation) {
    std::string output;
    unsigned int spaces = 0;
    bool escape = false;
    bool inString = false;

    for (size_t i = 0; i < json.size(); i++) {
        char symbol = json[i];

        if (escape) {
            output += symbol;
            escape = false;
            continue;
        } else if (inString) {
            inString = '"' != symbol;
            output += symbol;
            continue;
        }


        if ((symbol == '{' and json[i + 1] != '}') or (symbol == '[' and json[i + 1] != ']')) {
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        } else if ((symbol == '}' and json[i - 1] != '{') or (symbol == ']' and json[i - 1] != '[')) {
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        } else if (symbol == ',') {
            output += ",\n" + std::string(spaces - 1, ' ');
        } else {
            if (symbol == '\\') {
                escape = true;
            } else if (symbol == '"') {
                inString = true;
            }

            output += symbol;
        }

        continue;

        if (symbol == '\\' and !escape) {
            output += symbol;
            escape = true;
            continue;
        } else if (symbol == '\"' and !escape) {
            output += symbol;
            inString = !inString;
        } else if ((symbol == '{' or symbol == '[') and !inString) {
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        } else if ((symbol == '}' or symbol == ']') and !inString) {
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        } else if (symbol == ',' and !inString) {
            output += ",\n" + std::string(spaces - 1, ' ');
        } else output += symbol;

        escape = false;
    }

    return output;
}

std::string Tools::doubleToString(const double &dou) {
    std::string str = std::to_string(dou);
    if (str.find('.') != std::string::npos) {
        while (str.back() == '0' and str[str.length() - 2] != '.') {
            str.pop_back();
        }
    }
    return str;
}


std::string toString(Type type) {
    switch (type) {
        case INTEGER:
            return "INTEGER";
        case BOOLEAN:
            return "BOOLEAN";
        case FRACTION:
            return "FLOATING POINT";
        case OBJECT:
            return "JSON OBJECT";
        case STRING:
            return "STRING";
        case ARRAY:
            return "JSON ARRAY";
        case JSON_NULL:
            return "JSON NULL";
        case UNINITIALIZED:
            return "UNINITIALIZED";
    }
}
} // namespace JsonMax
#endif //JSONMAX_H
