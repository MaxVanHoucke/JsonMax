/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_EXCEPTIONS_H
#define JSONMAX_EXCEPTIONS_H


#include "Element.h"
#include "Parser.h"
#include "Type.h"


namespace JsonMax {


    class TypeException : public std::runtime_error {
    protected:

        TypeException(Type actual, Type expected) : std::runtime_error(
                "Casting an element of type " + toString(actual) + " to " +
                toString(expected) + " is not possible.") {
        }

        explicit TypeException(const std::string &str) : std::runtime_error(str) {}

        friend class Element;
    };


    class ParseException : public std::runtime_error {
    protected:

        explicit ParseException(const std::string &message) : std::runtime_error(message) {}

        friend Element parse(const std::string &);

        friend Element parseFile(const std::string &);

        friend class Parser;

    };

}


#endif //JSONMAX_EXCEPTIONS_H
