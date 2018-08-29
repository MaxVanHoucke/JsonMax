/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONELEMENT_H
#define JSONMAX_JSONELEMENT_H

#include <string>
#include <vector>
#include "JsonObject.h"

class JsonElement {
public:

    JsonElement();

    operator=(std::string string);
    operator=(long num);
    operator=(double fract);
    operator=(JsonObject obj);
    operator=(const std::vector<JsonElement>& arr);

    operator const std::vector<JsonElement>&() const;
    operator double() const;
    operator long() const;
    operator std::string() const;

private:

    long number;
    bool boolean;
    double fraction;
    JsonObject object;
    std::string string;
    std::vector<JsonElement> array;

};

#endif //JSONMAX_JSONELEMENT_H
