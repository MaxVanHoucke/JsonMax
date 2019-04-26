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

    }

}

#endif //JSONMAX_TOOLS_H
