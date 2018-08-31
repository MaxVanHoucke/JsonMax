/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

#include "JsonElement.h"

class JsonParser {
public:

    static JsonElement parse(const std::string& json);

private:

};

#endif //JSONMAX_JSONPARSER_H
