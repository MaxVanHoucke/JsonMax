/**
 * @author Max Van Houcke
 */

#include "Type.h"

using namespace JsonMax;

std::string JsonMax::toString(Type type) {
    switch (type) {
        case INTEGER:
            return "INTEGER";
        case BOOLEAN:
            return "BOOLEAN";
        case FRACTION:
            return "FLOATING POINT";
        case OBJECT:
            return "JSON OBJECT";
        case STRING:
            return "STRING";
        case ARRAY:
            return "JSON ARRAY";
        case JSON_NULL:
            return "JSON NULL";
        case UNINITIALIZED:
            return "UNINITIALIZED";
    }
}