/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_TOOLS_H
#define JSONMAX_TOOLS_H


#include <string>

namespace JsonMax {

    namespace Tools {

        /// Indents the given string with the given indentation (in spaces)
        std::string indent(const std::string &json, int indentation);

        /// Returns the string representation of a double, without any trailing zeroes after the comma
        std::string doubleToString(const double&);

    }

}

#endif //JSONMAX_TOOLS_H
