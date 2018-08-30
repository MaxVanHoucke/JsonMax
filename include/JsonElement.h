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
        JSON_NULL
    };

    JsonElement();

    std::string toString(int indent) const;

    JsonElement& operator[](const std::string& string);
    JsonElement& operator[](const char* c_string);


    JsonElement& operator=(const std::string& string);
    JsonElement& operator=(const char* c_string);
    JsonElement& operator=(int num);
    JsonElement& operator=(double fract);
    JsonElement& operator=(bool boolean);
    JsonElement& operator=(JsonObject obj);
    JsonElement& operator=(const std::vector<JsonElement>& arr);

    operator long() const;
    operator bool() const;
    operator double() const;
    operator JsonObject*() const;
    operator std::string() const;
    operator const std::vector<JsonElement>&() const;

    void setNumber(long number);
    void setBoolean(bool boolean);
    void setFraction(double fraction);
    void setObject(JsonObject object);
    void setString(const std::string &string);
    void setArray(const std::vector<JsonElement> &array);

//    bool isNumber() const;
//    bool isBoolean() const;
//    bool isFraction() const;
//    bool isObject() const;
//    bool isString() const;
//    bool isArray() const;

private:


    Type type;

    long number;
    bool boolean;
    double fraction;
    JsonObject* object;
    std::string string;
    std::vector<JsonElement> array;

};

#endif //JSONMAX_JSONELEMENT_H
