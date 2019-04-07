/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

#include <iostream>
#include <stack>
#include "JsonElement.h"
#include "Object.h"

namespace JsonMax {

    JsonElement parse(const std::string &);


    namespace JsonParser {

        int findIndex(size_t start, char symbol, const std::string &string);

        int findEnding(size_t start, char symbol, const std::string &string);

        bool validateString(const std::string &string);

        bool validateNumber(const std::string &number);

        std::string trim(const std::string &string);

        Object parseObject(const std::string &object);

        JsonElement parseArray(const std::string &array);

    };

}



#endif //JSONMAX_JSONPARSER_H
