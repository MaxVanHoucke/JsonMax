/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_TYPE_H
#define JSONMAX_TYPE_H

#include <string>

namespace JsonMax {

    /// Possible types of a JSON Element
    enum Type {
        INTEGER,
        BOOLEAN,
        FRACTION,
        OBJECT,
        STRING,
        ARRAY,
        JSON_NULL,
        UNINITIALIZED
    };

    /// Returns string representation of a type
    std::string toString(Type type);

}

#endif //JSONMAX_TYPE_H
