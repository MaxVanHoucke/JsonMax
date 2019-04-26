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

    /// Forward declarations
    class Element;
    class Pair;

    /// Storage options for the Object
    enum Storage {
        HASHMAP,
        MAP,
        VECTOR
    };

    /// JSON Object representation
    class Object {
    public:

        /**
         * Constructor
         * Pick the storage type most suitable to your situation (see readme for more info)
         * @param storage the wanted storage type
         */
        explicit Object(Storage storage = HASHMAP);

        /**
         * Copy constructor
         * Deep copies all elements and uses the same storage type
         */
        Object(const Object&);

        /**
         * Move constructor
         * Moves the complete storage from the temp object
         */
        Object(Object&&) noexcept;

        /**
         * Copy assignment
         * Resets the current object
         * Deep copies all elements and uses the same storage type
         */
        Object& operator=(const Object&);

        /**
         * Move assignment
         * Resets the current object
         * Moves the complete storage from the temp object
         */
        Object& operator=(Object&&) noexcept;

        /**
         * Destructor
         * Cleans up resources
         */
        ~Object();

        /**
         * Fetches the Element with the given key
         * Creates a new one if not present
         * @param key str key of the object
         * @return element with the given key
         */
        Element &operator[](const std::string &key);

        /**
         * @param indent the wanted indentation (in spaces)
         * @return string representation of the object
         */
        std::string toString(unsigned int indent = 0) const;

        /**
         * Removes an item from the object
         * Does nothing when the object does not exist
         */
        void remove(const std::string&);

        /**
         * Fetches all pairs in the object
         * @return vector of pairs, easy to loop over
         */
        std::vector<Pair> pairs() const;

        /// @return amount of items in the object
        size_t size() const;

        /// @return true if the item with the given key exists
        bool exists(const std::string&) const;

        /// @return true if the object is empty
        bool empty() const;

        /// Clears all items from the object
        void clear();

    private:

        /// Cleans up resources
        void reset();

        /// Moves the given temp object to this
        void move(Object&&);

        /// Deep copies the given object to this
        void copy(const Object&);

        /// Union with pointer to the different kinds of storage types
        union Data {
            std::vector<std::pair<std::string, Element>>* elementsVector;
            std::map<std::string, Element>* elementsMap;
            std::unordered_map<std::string, Element>* elementsHashmap;
        };

        /// Actual data
        Data data;

        /// Storage type
        Storage storage;

    };

}


#endif //JSONMAX_JSONOBJECT_H
