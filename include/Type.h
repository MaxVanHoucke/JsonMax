/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_TYPE_H
#define JSONMAX_TYPE_H

#include <string>

namespace JsonMax {

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

    std::string toString(Type type);

}

#endif //JSONMAX_TYPE_H
