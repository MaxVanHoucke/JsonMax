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

        explicit ParseException(const std::string &message, const std::string &json, size_t pos)
                : std::runtime_error(craftMessage(message, json, pos)) {}

        static std::string craftMessage(const std::string &message, const std::string &json, size_t pos) {
            int line = 1;
            int lineStart = 0;
            for (int i = 0; i < pos; i++) {
                if (json[i] == '\n') {
                    line++;
                }
            }
            return "Error on Line " + std::to_string(line) + ": " + message;
        }

        friend class Parser;

    };

}

#endif //JSONMAX_PARSEEXCEPTION_H
