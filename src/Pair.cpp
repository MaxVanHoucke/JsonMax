/**
 * @author Max Van Houcke
 */

#include "../include/Pair.h"

using namespace JsonMax;

Pair::Pair(const std::string &str, const JsonMax::Element &ele): key(str), value(ele) {}

const std::string& Pair::getKey() const {
    return key;
}

const Element& Pair::getValue() const {
    return value;
}
