/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_EXCEPTIONS_H
#define JSONMAX_EXCEPTIONS_H


#include "JsonElement.h"
#include "JsonParser.h"
#include "Type.h"


namespace JsonMax {


    class JsonTypeException : public std::exception {
    public:

        friend class JsonElement;

        virtual const char *what() const throw() {
            return msg.c_str();
        }

    protected:

        JsonTypeException(Type actual, Type expected) {
            msg = "Casting an element of type " + toString(actual) + " to " +
                  toString(expected) + " is not possible.";
        }

        explicit JsonTypeException(const std::string &str) {
            msg = str;
        }

        std::string msg;

    };


    class JsonParsingException : public std::exception {
    public:

        friend JsonElement parse(const std::string &);
        friend JsonElement JsonParser::parseArray(const std::string&);
        friend Object JsonParser::parseObject(const std::string&);

        virtual const char *what() const throw() {
            return msg.c_str();
        }

    protected:

        JsonParsingException(const char *message) : msg(message) {}

        std::string msg;

    };

}


#endif //JSONMAX_EXCEPTIONS_H
