/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_MODEL_UTILS_H
#define JSONMAX_MODEL_UTILS_H


#include <string>

namespace JsonMax {

    namespace Utils {

        /// Indents the given string with the given indentation (in spaces)
        std::string indent(const std::string &json, int indentation);

        /// Returns the string representation of a double, without any trailing zeroes after the comma
        std::string doubleToString(const double&);

    }

}

#endif //JSONMAX_MODEL_UTILS_H
