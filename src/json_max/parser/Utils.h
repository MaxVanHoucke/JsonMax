//
// Created by max on 05/04/2020.
//

#ifndef JSONMAX_PARSER_UTILS_H
#define JSONMAX_PARSER_UTILS_H

#include <string>
#include <fstream>
#include <sstream>
#include "ParseException.h"

namespace JsonMax {

    namespace Utils {

        std::string fileToString(const std::string &fileName) {
            std::ifstream in(fileName);
            if (not in.good()) {
                throw ParseException("Couldn't open " + fileName);
            }
            std::ostringstream stream;
            stream << in.rdbuf();
            return stream.str();
        }

    }

}

#endif //JSONMAX_PARSER_UTILS_H
