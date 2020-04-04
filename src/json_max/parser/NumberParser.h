/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_NUMBERPARSER_H
#define JSONMAX_NUMBERPARSER_H

#include <string>
#include "Parser.h"

namespace JsonMax {

    class NumberParser : public Parser {
    public:

        NumberParser(const std::string &str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    public:

        static double parseNumber(const std::string& str);

    };

}


#endif //JSONMAX_NUMBERPARSER_H
