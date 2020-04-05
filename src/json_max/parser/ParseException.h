/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_PARSEEXCEPTION_H
#define JSONMAX_PARSEEXCEPTION_H

#include <exception>

namespace JsonMax {

    /// Runtime JSON parsing exception
    class ParseException : public std::runtime_error {
    public:

        explicit ParseException(const std::string &message) : std::runtime_error(message) {}

        friend class Parser;

    };

}

#endif //JSONMAX_PARSEEXCEPTION_H
