/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONELEMENT_H
#define JSONMAX_JSONELEMENT_H

#include <string>
#include <vector>

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

    class TypeException: public std::exception {
    public:

        TypeException(JsonElement::Type actual, JsonElement::Type expected) {
            msg = "Casting an element of type " + JsonElement::typeToString(actual) + " to " + JsonElement::typeToString(expected) + " is not possible.";
        }

        virtual const char* what() const throw() {
            return msg.c_str();
        }

    protected:

        std::string msg;

    };

    JsonElement();

    JsonElement(const std::string& string);
    JsonElement(const char* c_string);
    JsonElement(int num);
    JsonElement(double fract);
    JsonElement(bool boolean);
    JsonElement(const JsonObject& obj);
    JsonElement(const std::vector<JsonElement>& arr);

    std::string toString(unsigned int indent = 0) const;

    void setNULL();

    Type getType() const;

    JsonElement& operator[](const char* c_string);

    JsonElement& operator=(const std::string& string);
    JsonElement& operator=(const char* c_string);
    JsonElement& operator=(int num);
    JsonElement& operator=(double fract);
    JsonElement& operator=(bool boolean);
    JsonElement& operator=(const JsonObject& obj);
    JsonElement& operator=(const std::vector<JsonElement>& arr);

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



#endif //JSONMAX_JSONELEMENT_H
