/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_PAIR_H
#define JSONMAX_PAIR_H

#include <string>
#include "Element.h"

namespace JsonMax {

    /// Pair in a JSON Object
    class Pair {
    public:

        /// Constructor with key and value
        Pair(const std::string &, const Element &);

        /// Getter for key
        const std::string &getKey() const;

        /// Getter vor value
        const Element &getValue() const;

    private:

        std::string key;
        Element value;

    };

}

#endif //JSONMAX_PAIR_H
