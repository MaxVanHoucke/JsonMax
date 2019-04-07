/**
 * @author Max Van Houcke
 */

#include "../include/Iterator.h"
#include "../include/Element.h"

using namespace JsonMax;

Iterator::Iterator(int ind, const Object* obj) : index(ind), object(obj) {}

Iterator::Iterator(int ind, const std::vector<Element>* arr) : index(ind), array(arr) {}

Iterator Iterator::operator++() {
    ++index;
    return *this;
}

Iterator Iterator::operator++(int) {
    ++index;
    return *this;
}

bool Iterator::operator!=(const Iterator &other) const { return index != other.index; }

const Element& Iterator::operator*() const {
    if (object) {
        return *(object->elements[index].second);
    } else if (array) {
        return (*array)[index];
    }
}