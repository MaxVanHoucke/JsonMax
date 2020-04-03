//
// Created by max on 03/04/2020.
//

#ifndef JSONMAX_NUMBERPARSER_H
#define JSONMAX_NUMBERPARSER_H

#include <string>
#include "../model/Element.h"
#include "../model/Object.h"
#include "Parser.h"

namespace JsonMax {

    class NumberParser : public Parser {
    public:

        NumberParser(const std::string &str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    };

}


#endif //JSONMAX_NUMBERPARSER_H
