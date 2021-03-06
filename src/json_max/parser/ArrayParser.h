/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_ARRAYPARSER_H
#define JSONMAX_ARRAYPARSER_H

#include <string>
#include "../model/Element.h"
#include "../model/Object.h"
#include "Parser.h"

namespace JsonMax {

    /// Parses JSON arrays
    class ArrayParser: public Parser {
    public:

        ArrayParser(const std::string& str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    protected:

        void checkArraySemantics();

    };

}


#endif //JSONMAX_ARRAYPARSER_H
