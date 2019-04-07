/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_EXCEPTIONS_H
#define JSONMAX_EXCEPTIONS_H


#include "Element.h"
#include "Parser.h"
#include "Type.h"


namespace JsonMax {


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

}


#endif //JSONMAX_EXCEPTIONS_H
