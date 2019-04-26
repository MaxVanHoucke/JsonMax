/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_PAIR_H
#define JSONMAX_PAIR_H

#include <string>
#include "Element.h"

namespace JsonMax {

    class Pair {
    public:

        Pair(const std::string &, const Element &);

        const std::string &getKey() const;

        const Element &getValue() const;

    private:

        std::string key;

        Element value;

    };

}

#endif //JSONMAX_PAIR_H
