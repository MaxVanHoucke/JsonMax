/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

#include <stack>
#include "JsonElement.h"
#include "JsonObject.h"

class JsonParser {
public:

    static JsonElement parse(const std::string& json);

    static int findIndex(int start, char symbol, const std::string& string);

    static int findEnding(int start, char symbol, const std::string& string);

    static bool validateString(const std::string& string);

    static bool validateNumber(const std::string& number);

    static std::string trim(const std::string& string);

    static JsonObject parseObject(const std::string& object);

    static JsonElement parseArray(const std::string& array);

private:

    std::stack<JsonElement> elementStack;

};

#endif //JSONMAX_JSONPARSER_H
