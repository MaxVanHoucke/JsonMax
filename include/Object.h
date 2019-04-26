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
    class Pair;

    class Object {
    public:

        friend class Element;

        enum Storage {
            HASHMAP,
            MAP,
            VECTOR
        };

        /**
         * Constructor
         */
        explicit Object(Storage storage = HASHMAP);

        Object(const Object&);
        Object(Object&&) noexcept;

        Object& operator=(const Object&);
        Object& operator=(Object&&) noexcept;

        ~Object();

        /**
         * @param member
         * @return
         */
        Element &operator[](const std::string &member);

        std::string toString(unsigned int indent = 0) const;

        void remove(const std::string&);

        std::vector<Pair> pairs() const;

        size_t size() const;

        bool exists(const std::string&) const;

        bool empty() const;

        void clear();

    private:

        void reset();
        void move(Object&&);
        void copy(const Object&);

        /**
         * The elements of the object
         */


        union Data {
            std::vector<std::pair<std::string, Element>>* elementsVector;
            std::map<std::string, Element>* elementsMap;
            std::unordered_map<std::string, Element>* elementsHashmap;
        };

        Data data;

        Storage storage;

    };

}


#endif //JSONMAX_JSONOBJECT_H
