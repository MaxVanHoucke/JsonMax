/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONMAX_H
#define JSONMAX_JSONMAX_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

class JsonObject;

class JsonElement {
public:

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

    static std::string typeToString(Type type) {
        switch (type) {
            case INTEGER: return "INTEGER";
            case BOOLEAN: return "BOOLEAN";
            case FRACTION: return "FLOATING POINT";
            case OBJECT: return "JSON OBJECT";
            case STRING: return "STRING";
            case ARRAY: return "JSON ARRAY";
            case JSON_NULL: return "JSON NULL";
            case UNINITIALIZED: return "UNINITIALIZED";
        }
    }

    class JsonTypeException: public std::exception {
    public:

        JsonTypeException(JsonElement::Type actual, JsonElement::Type expected) {
            msg = "Casting an element of type " + JsonElement::typeToString(actual) + " to " + JsonElement::typeToString(expected) + " is not possible.";
        }

        JsonTypeException(const std::string& str) {
            msg = str;
        }

        virtual const char* what() const throw() {
            return msg.c_str();
        }

    protected:

        std::string msg;

    };

    static JsonElement null();

    JsonElement();


    JsonElement(const std::string& string);
    JsonElement(const char* c_string);
    JsonElement(int num);
    JsonElement(double fract);
    JsonElement(bool boolean);
    JsonElement(const JsonObject& obj);
    JsonElement(const std::vector<JsonElement>& arr);
    JsonElement(const std::initializer_list<JsonElement>& arr);
    JsonElement(std::nullptr_t pointer);


    std::string toString(unsigned int indent = 0) const;

    void setNULL();

    Type getType() const;

    JsonElement& operator[](const char* c_string);

    friend std::ostream& operator<<(std::ostream& out, const JsonElement& element);

    JsonElement& operator=(const std::string& string);
    JsonElement& operator=(const char* c_string);
    JsonElement& operator=(int num);
    JsonElement& operator=(double fract);
    JsonElement& operator=(bool boolean);
    JsonElement& operator=(const JsonObject& obj);
    JsonElement& operator=(const std::vector<JsonElement>& arr);
    JsonElement& operator=(const std::initializer_list<JsonElement>& arr);
    JsonElement& operator=(std::nullptr_t pointer);

    operator int() const;
    operator bool() const;
    operator double() const;
    operator JsonObject() const;
    operator std::string() const;
    operator const char*() const;
    operator std::vector<JsonElement>() const;


private:

    void checkType(Type castType) const;

    void setNumber(int number);
    void setBoolean(bool boolean);
    void setFraction(double fraction);
    void setObject(JsonObject object);
    void setString(const std::string &string);
    void setArray(const std::vector<JsonElement> &array);

    Type type;

    int number;
    bool boolean;
    double fraction;
    JsonObject* object;
    std::string string;
    std::vector<JsonElement> array;

};

std::ostream& operator<<(std::ostream&, const JsonElement&);


class JsonObject {
public:

    /**
     * Constructor
     */
    JsonObject() = default;

    /**
     * @param member
     * @return
     */
    JsonElement& operator[](const std::string& member);

    std::string toString(unsigned int indent = 0) const;

    static std::string indent(const std::string& json, int indentation);

private:

    /**
     * The elements of the object
     */
    std::vector<std::pair<std::string, JsonElement*>> elements;

};


class JsonParser {
public:

    class JsonParsingException: public std::exception {
    public:

        friend class JsonParser;

        virtual const char* what() const throw() {
            return msg.c_str();
        }

    protected:

        JsonParsingException(const char* message): msg(message) {}

        std::string msg;

    };

    static JsonElement parse(const std::string& json);

    static int findIndex(size_t start, char symbol, const std::string& string);

    static int findEnding(size_t start, char symbol, const std::string& string);

    static bool validateString(const std::string& string);

    static bool validateNumber(const std::string& number);

    static std::string trim(const std::string& string);

    static JsonObject parseObject(const std::string& object);

    static JsonElement parseArray(const std::string& array);

};



JsonElement& JsonObject::operator[](const std::string &member) {
    for (const auto& elem: elements)
    {
        if (elem.first == member)
        {
            return *elem.second;
        }
    }
    auto element = new JsonElement();
    elements.emplace_back(member, element);
    return *element;
}

std::string JsonObject::toString(unsigned int indent) const {
    std::string output = "{";
    for (const auto &elem: elements) {
        if (elem.second->getType() == JsonElement::UNINITIALIZED) {
            continue;
        }
        output += "\"" + elem.first + "\": " + elem.second->toString(0) + ", ";
    }
    if (output.size() > 2) {
        output.pop_back();
        output.pop_back();
    }
    output += "}";

    if (indent) {
        return JsonObject::indent(output, indent);
    }

    return output;
}

std::string JsonObject::indent(const std::string &json, int indentation) {
    std::string output;
    unsigned int spaces = 0;
    bool escape = false;
    bool inString = false;

    for (char symbol: json) {

        if (symbol == '\\' and !escape) {
            output += symbol;
            escape = true;
            continue;
        }
        else if (symbol == '\"' and !escape) {
            output += symbol;
            inString = !inString;
        }
        else if ((symbol == '{' or symbol == '[') and !inString) {
            spaces += indentation;
            output += std::string(1, symbol) + "\n" + std::string(spaces, ' ');
        }
        else if ((symbol == '}' or symbol == ']') and !inString) {
            spaces -= indentation;
            output += "\n" + std::string(spaces, ' ') + std::string(1, symbol);
        }
        else if (symbol == ',' and !inString) {
            output += ",\n" + std::string(spaces - 1, ' ');
        }
        else output += symbol;

        escape = false;
    }

    return output;
}


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
            return object->toString(indent);
        case STRING:
            return "\"" + string + "\"";
        case ARRAY: {
            std::string arrayElements = "[";
            for (int i = 0; i < array.size(); i++) {
                arrayElements += array[i].toString();
                if (i != array.size() - 1) arrayElements += ", ";
            }
            arrayElements += "]";
            if (indent) return JsonObject::indent(arrayElements, indent);
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

JsonElement::JsonElement(const JsonObject &obj) {
    setObject(obj);
}

JsonElement::JsonElement(const std::vector<JsonElement> &arr) {
    setArray(arr);
}

JsonElement& JsonElement::operator=(std::nullptr_t pointer) {
    if (pointer == nullptr) {
        type = JSON_NULL;
    } else {

    }
}

JsonElement JsonElement::null() {
    JsonElement element;
    element.setNULL();
    return element;
}

JsonElement::JsonElement(std::nullptr_t pointer) {
    if (pointer == nullptr) {
        type = JSON_NULL;
    }
}

JsonElement::JsonElement(const std::initializer_list<JsonElement> &arr) {
    setArray(arr);
}

JsonElement& JsonElement::operator=(const std::initializer_list<JsonElement> &arr) {
    setArray(arr);
}

std::ostream& operator<<(std::ostream& out, const JsonElement& element) {
    std::string output = element.toString();
    if (!output.empty() and output.front() == '"' and output.back() == '"') {
        output.pop_back();
        if (!output.empty()) output.erase(0, 1);
    }
    out << output;
    return out;
}



JsonElement JsonParser::parse(const std::string &json) {
    std::string element = trim(json);

    if (element == "true") {
        return JsonElement(true);
    } else if (element == "false") {
        return JsonElement(false);
    } else if (element == "null") {
        return JsonElement(nullptr);
    }

    JsonElement output;

    if (element.empty()) {
        return JsonElement();
    }

    if (element[0] == '{') {
        if (element.back() != '}') {
            throw JsonParsingException("Invalid Json: object does not end with '}'");
        }
        return parseObject(element.substr(1, element.size() - 2));
    }

    if (element[0] == '[') {
        if (element.back() != ']') {
            throw JsonParsingException("Invalid Json: array does not end with '}'");
        }
        return parseArray(element.substr(1, element.size() - 2));
    }

    if (validateNumber(element)) {
        try {
            double number = std::stod(element);
            if (element.find('.') == std::string::npos) {
                return JsonElement((int) number);
            }
            else return JsonElement(number);
        } catch (std::out_of_range& e) {
            throw JsonParsingException(std::string("Cannot parse, number '" + element + "' is out of range.").c_str());
        } catch (std::invalid_argument& e) {
            throw JsonParsingException(std::string("Invalid Json, number '" + element + "' is not valid.").c_str());
        }
    }

    if (element[0] == '"') {
        if (element.back() != '"') {
            throw JsonParsingException(std::string("Invalid Json, string " + element + " has no ending.").c_str());
        }
        if (!validateString(element.substr(1, element.size() - 2))) {
            throw JsonParsingException(std::string("Invalid Json, string " + element + " is invalid as per Json rules.").c_str());

        }
        return JsonElement(element.substr(1, element.size() - 2));
    }

    throw JsonParsingException(std::string("Invalid Json, element " + element + " is not a supported type.").c_str());
}

int JsonParser::findIndex(size_t start, char symbol, const std::string &string) {
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

bool JsonParser::validateNumber(const std::string &number) {
    unsigned int index = 0;
    bool valid = false;

    try
    {
        if (number.at(0) == '-') {
            index++;
        }

        if (number.at(index) == '0') {
            index++;
            goto point;
        }
        else if (isdigit(number.at(index))) {
            valid = true;
            while (isdigit(number.at(index))) {
                index++;
            }
        }
        else return false;

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
        }
        else return false;

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
    catch (std::out_of_range& exception) {
        return valid;
    }
}

bool JsonParser::validateString(const std::string &string) {
    bool escape = false;

    for (int i = 0; i < string.size(); i++) {
        char symbol = string[i];

        if (escape) {
            if (not (symbol == '"' or symbol == '\\'
                     or symbol == '/' or symbol == 'b'
                     or symbol == 'f' or symbol == 'n'
                     or symbol == 'r' or symbol == 't'
                     or symbol == 'u')) return false;

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
        }
        else if (symbol == '\\') {
            escape = true;
        }
        else if (symbol == '\"') {
            return false;
        }
    }
    return true;
}

std::string JsonParser::trim(const std::string &str) {
    const auto strBegin = str.find_first_not_of(" \t\n");
    if (strBegin == std::string::npos) return "";
    const auto strEnd = str.find_last_not_of(" \t\n");
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}


JsonElement JsonParser::parseArray(const std::string &array) {
    std::string element = trim(array);

    if (element.empty()) {
        return JsonElement(std::vector<JsonElement>());
    }

    std::vector<JsonElement> jsonArray;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            break;
        }

        if (element[index] == '{') {
            int i = findEnding(index, '{', element);
            if (i == -1) {
                throw JsonParsingException("Invalid Json: object does not end with '}'");
            }

            jsonArray.push_back(parse(element.substr(index, i - index + 1)));
            index = i + 1;
        }

        else if (element[index] == '[') {
            int i = findEnding(index, '[', element);
            if (i == -1) {
                throw JsonParsingException("Invalid Json: array does not end with ']'");
            }

            jsonArray.push_back(parse(element.substr(index, i - index + 1)));
            index = i + 1;
        }

        else {
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
            throw JsonParsingException("Invalid Json: invalid characters after value");
        }

        index++;
    }

    return JsonElement(jsonArray);
}

JsonObject JsonParser::parseObject(const std::string &object) {
    std::string element = trim(object);

    if (element.empty()) {
        return JsonObject();
    }

    JsonObject json;

    size_t index = 0;
    while (true) {

        index = element.find_first_not_of(" \t\n", index);
        if (index == std::string::npos or element[index] != '"') {
            throw JsonParsingException(std::string("Invalid Json, key in object missing").c_str());
        }

        int i = findIndex(index + 1, '"', element);
        if (i == -1) {
            throw JsonParsingException(std::string("Invalid Json, key in object has no ending").c_str());
        }

        std::string key = element.substr(index + 1, i - index - 1);

        index = size_t(i) + 1;
        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos or element[index] != ':') {
            throw JsonParsingException(std::string("Invalid Json, no ':' between key and value").c_str());
        }

        index++;

        index = element.find_first_not_of(" \t\n", index);

        if (index == std::string::npos) {
            throw JsonParsingException(std::string("Invalid Json, key without value.").c_str());
        }

        if (element[index] == '{') {
            int i = findEnding(index, '{', element);
            if (i == -1) {
                throw JsonParsingException("Invalid Json: object does not end with '}'");
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        }

        else if (element[index] == '[') {
            int i = findEnding(index, '[', element);
            if (i == -1) {
                throw JsonParsingException("Invalid Json: array does not end with ']'");
            }

            json[key] = parse(element.substr(index, i - index + 1));
            index = i + 1;
        }

        else {
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
            throw JsonParsingException("Invalid Json: invalid characters after value");
        }

        index++;
    }

    return json;
}


int JsonParser::findEnding(size_t start, char symbol, const std::string& string) {
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
        }
        else if (sym == '"') {
            inString = !inString;
        }
        else if (sym == symbol and !inString) {
            startCount++;
        }
        else if (sym == endSymbol and !inString) {
            endCount++;

            if (startCount == endCount) {
                return i;
            }
        }
    }
    return -1;
}


#endif //JSONMAX_JSONMAX_H
