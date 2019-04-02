/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

#include <iostream>
#include <stack>
#include "JsonElement.h"
#include "JsonObject.h"


JsonElement parse(const std::string&);


class JsonParser {
private:

    friend JsonElement parse(const std::string&);

    static int findIndex(size_t start, char symbol, const std::string &string);
    static int findEnding(size_t start, char symbol, const std::string &string);

    static bool validateString(const std::string &string);
    static bool validateNumber(const std::string &number);

    static std::string trim(const std::string &string);

    static Object parseObject(const std::string &object);
    static JsonElement parseArray(const std::string &array);

};

class JsonParsingException : public std::exception {
public:

    friend class JsonParser;
    friend JsonElement parse(const std::string&);

    virtual const char *what() const throw() {
        return msg.c_str();
    }

protected:

    JsonParsingException(const char *message) : msg(message) {}

    std::string msg;

};

#endif //JSONMAX_JSONPARSER_H
