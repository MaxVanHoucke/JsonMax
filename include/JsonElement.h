/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONELEMENT_H
#define JSONMAX_JSONELEMENT_H

#include <string>
#include <vector>

class Object;

class JsonElement {
public:

    friend std::ostream &operator<<(std::ostream &out, const JsonElement &element);

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

    JsonElement();
    JsonElement(const std::string &string);
    JsonElement(const char *old_string);
    JsonElement(int num);
    JsonElement(double fraction);
    JsonElement(bool boolean);
    JsonElement(const Object &obj);
    JsonElement(const std::vector<JsonElement> &arr);
    JsonElement(const std::initializer_list<JsonElement> &arr);
    JsonElement(std::nullptr_t pointer);

    Type getType() const;
    JsonElement &operator[](const char *c_string);
    std::string toString(unsigned int indent = 0) const;

    JsonElement &operator=(const std::string &string);
    JsonElement &operator=(const char *c_string);
    JsonElement &operator=(int num);
    JsonElement &operator=(double fract);
    JsonElement &operator=(bool boolean);
    JsonElement &operator=(const Object &obj);
    JsonElement &operator=(const std::vector<JsonElement> &arr);
    JsonElement &operator=(const std::initializer_list<JsonElement> &arr);
    JsonElement &operator=(std::nullptr_t pointer);

    operator int() const;
    operator bool() const;
    operator double() const;
    operator Object() const;
    operator std::string() const;
    operator const char *() const;
    operator std::vector<JsonElement>() const;

private:

    void checkType(Type castType) const;

    void setNumber(int number);
    void setBoolean(bool boolean);
    void setFraction(double fraction);
    void setObject(Object object);
    void setString(const std::string &string);
    void setArray(const std::vector<JsonElement> &array);

    Type type;

    int number;
    bool boolean;
    double fraction;
    Object *object;
    std::string string;
    std::vector<JsonElement> array;

};

class JsonTypeException : public std::exception {
public:

    JsonTypeException(JsonElement::Type actual, JsonElement::Type expected) {
        msg = "Casting an element of type " + JsonElement::typeToString(actual) + " to " +
              JsonElement::typeToString(expected) + " is not possible.";
    }

    JsonTypeException(const std::string &str) {
        msg = str;
    }

    virtual const char *what() const throw() {
        return msg.c_str();
    }

protected:

    std::string msg;

};


std::ostream& operator<<(std::ostream&, const JsonElement&);


#endif //JSONMAX_JSONELEMENT_H
