/**
 * @author Max Van Houcke
 */

#include "Pair.h"

using namespace JsonMax;

Pair::Pair(std::string str, JsonMax::Element ele): key(std::move(str)), value(std::move(ele)) {}

const std::string& Pair::getKey() const {
    return key;
}

const Element& Pair::getValue() const {
    return value;
}
