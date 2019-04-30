/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONELEMENT_H
#define JSONMAX_JSONELEMENT_H

#include <string>
#include <vector>
#include "Type.h"

namespace JsonMax {

    /// Forward declarations
    class Object;
    class Element;

    /// Name alias for a Json Array
    using Array = std::vector<Element>;

    /**
     * Representation of an Element in a JSON Object
     */
    class Element {
    public:

        /// Default constructor, sets type to uninitialized
        Element();

        /// Copy constructor
        Element(const Element&);

        /// Move constructor
        Element(Element&&) noexcept;

        /// Constructor for string
        Element(const std::string &string);

        /// Constructor for c string
        Element(const char *old_string);

        /// Constructor for int
        Element(int num);

        /// Constructor for double
        Element(double fraction);

        /// Constructor for boolean
        Element(bool boolean);

        /// Constructor for a JSON Object
        Element(const Object &obj);

        /// Constructor for a JSON Array
        Element(const Array &arr);

        /// Constructor for a JSON Array (initializer list)
        Element(const std::initializer_list<Element> &arr);

        /// Constructor for JSON null
        Element(std::nullptr_t pointer);

        /// Destructor, cleans up resources
        ~Element();

        /// Copy assignment
        Element& operator=(const Element&);

        /// Move assignment
        Element& operator=(Element&&) noexcept;

        /// String assignment
        Element &operator=(const std::string &string);

        /// C string assignment
        Element &operator=(const char *c_string);

        /// Int assignment
        Element &operator=(int num);

        /// Double assignment
        Element &operator=(double fract);

        /// Boolean assignment
        Element &operator=(bool boolean);

        /// JSON Object assignment
        Element &operator=(const Object &obj);

        /// JSON Array assignment
        Element &operator=(const Array &arr);

        /// JSON Array (initializer list) assignment
        Element &operator=(const std::initializer_list<Element> &arr);

        /// JSON null assignment
        Element &operator=(std::nullptr_t pointer);

        /// Getter for the current type
        Type getType() const;

        /// Returns the operator[] of the Object, throws exception if not an Object
        Element &operator[](const std::string&);

        /**
         * @param indent the wanted indentation (in spaces)
         * @return string representation of the object
         */
        std::string toString(unsigned int indent = 0) const;

        /// Int getter, throws type exception if wrong type
        int getInt() const;

        /// Boolean getter, throws type exception if wrong type
        bool getBool() const;

        /// Double getter, throws type exception if wrong type
        double getDouble() const;

        /// String getter, throws type exception if wrong type
        std::string& getString() const;

        /// Object getter, throws type exception if wrong type
        Object& getObject() const;

        /// Array getter, throws type exception if wrong type
        Array& getArray() const;
        
        /// Check if type is int
        bool isInt() const;

        /// Check if type is bool
        bool isBool() const;
        
        /// Check if type is double
        bool isDouble() const;

        /// Check if type is string
        bool isString() const;

        /// Check if type is JSON Object
        bool isObject() const;

        /// Check if type is JSON Array
        bool isArray() const;

        /// Check if type is JSON Null
        bool isNull() const;

    private:

        /// Moves the given temp object to this
        void move(Element&&);

        /// Deep copies the given object to this
        void copy(const Element&);

        /// Cleans up resources
        void reset();

        /// Throws a TypeException if the given type is not equal to the current one
        void checkType(Type castType) const;

        /// Makes the element an integer
        void setNumber(int number);

        /// Makes the element a boolean
        void setBoolean(bool boolean);

        /// Makes the element a fraction
        void setFraction(double fraction);

        /// Makes the element an object
        void setObject(const Object& object);

        /// Makes the element a string
        void setString(const std::string& string);

        /// Makes the element an array
        void setArray(const Array& array);

        /// Union with pointers to the different kinds of types
        union Data {
            int* number;
            bool boolean;
            double* fraction;
            Object* object;
            std::string* string;
            Array* array;
        };

        /// Actual data
        Data data;

        /// Element type
        Type type;

    };

}

#endif //JSONMAX_JSONELEMENT_H
