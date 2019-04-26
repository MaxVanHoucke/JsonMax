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
        Object(Object&&);

        Object& operator=(const Object&);
        Object& operator=(Object&&);



        ~Object();

        /**
         * @param member
         * @return
         */
        Element &operator[](const std::string &member);

        std::string toString(unsigned int indent = 0) const;

        void remove(const std::string&);


    private:

        void reset();
        void move(Object&&);
        void copy(const Object&);

        /**
         * The elements of the object
         */


        union Data {
            std::vector<std::pair<std::string, Element>>* elementsVector;
            std::map<std::string, Element*>* elementsMap;
            std::unordered_map<std::string, Element*>* elementsHashmap;
        };

        Data data;

        Storage storage;

    };

}


#endif //JSONMAX_JSONOBJECT_H
