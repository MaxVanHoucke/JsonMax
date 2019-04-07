/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONOBJECT_H
#define JSONMAX_JSONOBJECT_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>


namespace JsonMax {

    class Element;
    class Iterator;

    class Object {
    public:

        friend class Iterator;
        friend class Element;

        /**
         * Constructor
         */
        Object() = default;

        /**
         * @param member
         * @return
         */
        Element &operator[](const std::string &member);

        std::string toString(unsigned int indent = 0) const;


    private:

        /**
         * The elements of the object
         */
        std::vector<std::pair<std::string, Element *>> elements;

    };

}


#endif //JSONMAX_JSONOBJECT_H
