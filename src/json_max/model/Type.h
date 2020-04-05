/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_TYPE_H
#define JSONMAX_TYPE_H

#include <stdexcept>

namespace JsonMax {

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

}

#endif //JSONMAX_TYPE_H
