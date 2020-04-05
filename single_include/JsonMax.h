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

    /// Forward declaration
    class Element;

    /// Runtime Type mismatch exception
    class TypeException : public std::runtime_error {
    protected:

        TypeException(Type actual, Type expected) : std::runtime_error(
                "Casting an element of type " + toString(actual) + " to " +
                toString(expected) + " is not possible.") {
        }

        explicit TypeException(const std::string &str) : std::runtime_error(str) {}

        friend class Element;
    };



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



    namespace Utils {

        /// Indents the given string with the given indentation (in spaces)
        std::string indent(const std::string &json, int indentation);

        /// Returns the string representation of a double, without any trailing zeroes after the comma
        std::string doubleToString(const double&);

    }



    /// Runtime JSON parsing exception
    class ParseException : public std::runtime_error {
    public:

        explicit ParseException(const std::string &message) : std::runtime_error(message) {}

        friend class Parser;

    };



    namespace Utils {

        std::string fileToString(const std::string &fileName) {
            std::ifstream in(fileName);
            if (not in.good()) {
                throw ParseException("Couldn't open " + fileName);
            }
            std::ostringstream stream;
            stream << in.rdbuf();
            return stream.str();
        }

    }



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


    /**
     * Main Parser class
     * Can parse any JSON string.
     * Base class for all other parsers such as ObjectParser etc
     */
    class Parser {
    public:

        /// Constructor, stores the reference of a JSON string
        explicit Parser(const std::string& str) : Parser(str, 0, str.size()) {}

        /// Constructor, takes JSON but also the start and end positions (end position is not including)
        Parser(const std::string& str, size_t start, size_t end) : json(str), index(start), endIndex(end) {}

        /// Parses the stored json
        virtual Element parse();

    protected:

        /**
         *  Returns true if end of parsing is reached
         *  This also includes being positioned on the last char of the json
         */
        bool endOfParsing() const;

        /**
         * Finds the given symbol in the json, starting from the current position
         * Skips any element such as an object, array or string
         * @return the index of the symbol
         */
        size_t findIndexAfterElement(char symbol);

        /// Returns the stored json
        const std::string& getJson() const;

        /// Remaining characters in the json, includes the current position
        size_t remainingSize() const;

        /// Returns the current position/index
        size_t currentPosition() const;

        /// Returns the char in the json at the current position
        char currentSymbol() const;

        /// Returns the last position/index (which is still part of the json)
        size_t lastPosition() const;

        /// Incrementer for the position
        void incrementPosition();

        /// Setter for the position
        void setPosition(size_t pos);

        /// Trims any whitespace at the end by adjusting the endIndex/lastPosition
        void trimEndWhitespace();

        /// Moves the position to the first element that is not whitespace
        void moveToNonEmptyPosition();

        /// Trims the whitespace around the element
        void trim();

    private:

        /// Reference to the json string parsed
        const std::string& json;

        /// Current index in the json
        size_t index;

        /// One after the last index of the json
        size_t endIndex;

    };



    /// Parses JSON arrays
    class ArrayParser: public Parser {
    public:

        ArrayParser(const std::string& str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    protected:

        void checkArraySemantics();

    };



    /// Parses integers and doubles
    class NumberParser : public Parser {
    public:

        NumberParser(const std::string &str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    public:

        static double parseNumber(const std::string& str);

    };



    /// Parses JSON objects
    class ObjectParser: public Parser {
    public:

        ObjectParser(const std::string& str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    protected:

        std::string extractKeyAndAdjustIndex();

        void checkForDoublePointAndAdjustIndex();

        void checkObjectSemantics();

    };



    /**
     * Parses JSON strings
     * Mainly checks if they adhere to the standard
     */
    class StringParser : public Parser {
    public:

        StringParser(const std::string &str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    protected:

        bool isValidString();

        bool isHexadecimalCorrect();

        bool isEscapedPartCorrect();

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
            return Utils::doubleToString(*data.fraction);
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
            if (ind) return Utils::indent(arrayElements, ind);
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
        return Utils::indent(output, ind);
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


std::string Utils::indent(const std::string &json, int indentation) {
    std::string output;
    unsigned int spaces = 0;
    bool escape = false;
    bool inString = false;

    for (size_t i = 0; i < json.size(); i++) {
        char symbol = json[i];

        // Two special cases, escaped symbol or in string
        if (escape) {
            output += symbol;
            escape = false;
            continue;
        } else if (inString) {
            inString = '"' != symbol;
            output += symbol;
            continue;
        }

        // Non empty object or array started
        if ((symbol == '{' and json[i + 1] != '}') or (symbol == '[' and json[i + 1] != ']')) {
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        }
        // Non empty object or array ended
        else if ((symbol == '}' and json[i - 1] != '{') or (symbol == ']' and json[i - 1] != '[')) {
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        }
        // Comma so new line and indent
        else if (symbol == ',') {
            output += ",\n" + std::string(spaces - 1, ' ');
        }
        // Other symbols
        else {
            // Check if escape or string started
            if (symbol == '\\') {
                escape = true;
            } else if (symbol == '"') {
                inString = true;
            }
            output += symbol;
        }
    }

    return output;
}

std::string Utils::doubleToString(const double &dou) {
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


Element parse(const std::string &json) {
    return Parser(json).parse();
}

Element parseFile(const std::string &fileName) {
    std::string fileContent = Utils::fileToString(fileName);
    return parse(fileContent);
}

Element Parser::parse() {
    trim();
    size_t size = remainingSize();

    if (size == 0) {
        return Element();
    } else if (size == 4 and json.substr(index, size) == "true") {
        return Element(true);
    } else if (size == 5 and json.substr(index, size) == "false") {
        return Element(false);
    } else if (size == 4 and json.substr(index, size) == "null") {
        return Element(nullptr);
    } else if (currentSymbol() == '{') {
        return ObjectParser(json, index, endIndex).parse();
    } else if (currentSymbol() == '[') {
        return ArrayParser(json, index, endIndex).parse();
    } else if (currentSymbol() == '"') {
        return StringParser(json, index, endIndex).parse();
    } else {
        return NumberParser(json, index, endIndex).parse();
    }
}

void Parser::moveToNonEmptyPosition() {
    index = json.find_first_not_of(" \t\n", index);
    if (index == std::string::npos) {
        index = endIndex;
    }
}


void Parser::trim() {
    moveToNonEmptyPosition();
    trimEndWhitespace();
}


bool Parser::endOfParsing() const {
    return index == std::string::npos or index >= endIndex - 1;
}

void Parser::trimEndWhitespace() {
    endIndex = getJson().find_last_not_of(" \t\n", lastPosition());
    if (endIndex == std::string::npos) {
        endIndex = index;
    } else {
        endIndex++;
    }
}

size_t Parser::findIndexAfterElement(char symbol) {
    bool skip = false;
    bool inString = false;

    int arrayCounter = 0;
    int objectCounter = 0;
    for (size_t i = index; i < json.size(); i++) {
        char current = json[i];

        if (skip) {
            skip = false;
            continue;
        } else if (inString) {
            inString = current != '"';
            continue;
        }

        if (current == symbol and objectCounter == 0 and arrayCounter == 0) {
            return i;
        }

        if (current == '\\') {
            skip = true;
        } else if (current == '"') {
            inString = true;
        } else if (current == '{') {
            objectCounter++;
        } else if (current == '}') {
            objectCounter--;
        } else if (current == '[') {
            arrayCounter++;
        } else if (current == ']') {
            arrayCounter--;
        }
    }

    return std::string::npos;
}

size_t Parser::remainingSize() const {
    return endIndex - index;
}

const std::string& Parser::getJson() const {
    return json;
}

size_t Parser::currentPosition() const {
    return index;
}

size_t Parser::lastPosition() const {
    return endIndex - 1;
}

void Parser::incrementPosition() {
    index++;
}

void Parser::setPosition(size_t pos) {
    index = pos;
}

char Parser::currentSymbol() const {
    return getJson().at(currentPosition());
}


Element ArrayParser::parse() {
    trim();
    checkArraySemantics();
    // Skip '['
    incrementPosition();

    Array array;
    while (not endOfParsing()) {
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition();
        }
        array.push_back(Parser(getJson(), currentPosition(), endIndexOfElement).parse());
        setPosition(endIndexOfElement + 1);
    }
    return array;
}

void ArrayParser::checkArraySemantics() {
    if (currentSymbol() != '[') {
        throw ParseException("Invalid Json: object does not start with '{'");

    }
    if (getJson().at(lastPosition()) != ']') {
        throw ParseException("Invalid Json: array does not end with ']'");
    }
}


Element NumberParser::parse() {
    trim();
    std::string str = getJson().substr(currentPosition(), remainingSize());
    double number = parseNumber(str);
    if (str.find('.') == std::string::npos) {
        return Element((int) number);
    } else {
        return Element(number);
    }
}

double NumberParser::parseNumber(const std::string& str) {
    try {
        return std::stod(str);
    } catch (std::out_of_range &e) {
        throw ParseException("Cannot parse, number '" + str + "' is out of range.");
    } catch (std::invalid_argument &e) {
        throw ParseException("Invalid Json, '" + str + "' is not valid.");
    }
}


Element ObjectParser::parse() {
    trim();
    checkObjectSemantics();
    incrementPosition();

    Object obj = Object();
    while (not endOfParsing()) {
        std::string key = extractKeyAndAdjustIndex();
        checkForDoublePointAndAdjustIndex();
        size_t endIndexOfElement = findIndexAfterElement(',');
        if (endIndexOfElement == std::string::npos) {
            endIndexOfElement = lastPosition();
        }
        obj[key] = Parser(getJson(), currentPosition(), endIndexOfElement).parse();
        setPosition(endIndexOfElement + 1);
    }
    return obj;
}



std::string ObjectParser::extractKeyAndAdjustIndex() {
    // First quotation mark
    moveToNonEmptyPosition();
    if (endOfParsing() or currentSymbol() != '"') {
        throw ParseException("Invalid Json, missing key in object");
    }
    incrementPosition();

    int keyStart = currentPosition();

    // Second quotation mark
    setPosition(findIndexAfterElement('"'));
    if (endOfParsing()) {
        throw ParseException("Invalid Json, key in object has no ending");
    }
    incrementPosition();

    return getJson().substr(keyStart, currentPosition() - keyStart - 1);
}



void ObjectParser::checkForDoublePointAndAdjustIndex() {
    moveToNonEmptyPosition();
    if (endOfParsing() or currentSymbol() != ':') {
        throw ParseException("Invalid Json, no ':' between key and value");
    }
    incrementPosition();
}

void ObjectParser::checkObjectSemantics() {
    if (currentSymbol() != '{') {
        throw ParseException("Invalid Json: object does not start with '{'");

    }
    if (getJson().at(lastPosition()) != '}') {
        throw ParseException("Invalid Json: object does not end with '}'");
    }
}





Element StringParser::parse() {
    trim();
    if (not isValidString()) {
        throw ParseException("Invalid Json, string is invalid as per Json rules.");
    }
    // pos + 1 and size - 2 to erase quotation
    return getJson().substr(currentPosition() + 1, remainingSize() - 2);
}

bool StringParser::isValidString() {
    size_t startPosition = currentPosition();

    if (remainingSize() < 2 or currentSymbol() != '"' or getJson().at(lastPosition()) != '"') {
        return false;
    }
    incrementPosition();

    bool escape = false;
    while (not endOfParsing()) {
        if (escape) {
            if (not isEscapedPartCorrect()) {
                return false;
            }
            escape = false;
        } else if (currentSymbol() == '\\') {
            escape = true;
        } else if (currentSymbol() == '\"' and currentPosition() != lastPosition()) {
            return false;
        }
        incrementPosition();
    }
    setPosition(startPosition);
    return true;
}


bool StringParser::isHexadecimalCorrect() {
    if (currentPosition() + 4 > lastPosition()) {
        return false;
    }
    incrementPosition();
    const static std::string hexa = "0123456789abcdefABCDEF";
    size_t result = getJson().find_first_not_of(hexa.c_str(), currentPosition(), 4);
    return result != std::string::npos;
}


bool StringParser::isEscapedPartCorrect() {
    // Allowed chars after escape
    const static std::string allowed = "\"\\/bfnrtu";
    if (allowed.find(currentSymbol()) == std::string::npos) {
        return false;
    }
    // u has to be followed by 4 hexadecimal units
    return currentSymbol() != 'u' or isHexadecimalCorrect();
}
} // namespace JsonMax
#endif //JSONMAX_H
