//
// Created by max on 03/04/2020.
//

#ifndef JSONMAX_STRINGPARSER_H
#define JSONMAX_STRINGPARSER_H

#include <string>
#include "../model/Element.h"
#include "../model/Object.h"
#include "Parser.h"

namespace JsonMax {

    class StringParser : public Parser {
    public:

        StringParser(const std::string& str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

        bool isValidString();

        bool isHexadecimalCorrect();

        bool isEscapedPartCorrect();

    };

}

#endif //JSONMAX_STRINGPARSER_H
