/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_OBJECTPARSER_H
#define JSONMAX_OBJECTPARSER_H

#include <string>
#include "../model/Element.h"
#include "../model/Object.h"
#include "Parser.h"

namespace JsonMax {

    class ObjectParser: public Parser {
    public:

        ObjectParser(const std::string& str, size_t start, size_t end) : Parser(str, start, end) {}

        Element parse() override;

    protected:

        std::string extractKeyAndAdjustIndex();

        void checkForDoublePointAndAdjustIndex();

    };

}

#endif //JSONMAX_OBJECTPARSER_H
