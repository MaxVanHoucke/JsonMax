/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_ITERATOR_H
#define JSONMAX_ITERATOR_H

#include "Object.h"


namespace JsonMax {

    class Element;

    class Iterator {
    public:

        Iterator(int ind, const Object* obj);

        Iterator(int ind, const std::vector<Element>* arr);

        Iterator operator++();

        Iterator operator++(int);

        bool operator!=(const Iterator &other) const;

        const Element &operator*() const;

    private:

        int index;
        const Object* object;
        const std::vector<Element>* array;

    };

}


#endif //JSONMAX_ITERATOR_H
