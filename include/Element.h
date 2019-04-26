/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONELEMENT_H
#define JSONMAX_JSONELEMENT_H

#include <string>
#include <vector>

#include "Type.h"

namespace JsonMax {

    class Object;
    class Element;
    using Array = std::vector<Element>;

    class Element {
    public:


        Type getType() const;
        Element &operator[](const char *c_string);
        Element &operator[](const std::string&);
        std::string toString(unsigned int indent = 0) const;

        /**
         * Constructors
         */

        Element();
        Element(const std::string &string);
        Element(const char *old_string);
        Element(int num);
        Element(double fraction);
        Element(bool boolean);
        Element(const Object &obj);
        Element(const Array &arr);
        Element(const std::initializer_list<Element> &arr);
        Element(std::nullptr_t pointer);

        Element(const Element&);
        Element(Element&&);

        Element& operator=(const Element&);
        Element& operator=(Element&&);

        ~Element();


        /**
         * Operator=
         */

        Element &operator=(const std::string &string);
        Element &operator=(const char *c_string);
        Element &operator=(int num);
        Element &operator=(double fract);
        Element &operator=(bool boolean);
        Element &operator=(const Object &obj);
        Element &operator=(const Array &arr);
        Element &operator=(const std::initializer_list<Element> &arr);
        Element &operator=(std::nullptr_t pointer);

        /**
         * Type operators
         */

        int getInt() const;
        bool getBool() const;
        double getDouble() const;
        std::string& getString() const;
        Object& getObject() const;
        Array& getArray() const;

    private:

        void reset();
        void checkType(Type castType) const;

        void setNumber(int number);
        void setBoolean(bool boolean);
        void setFraction(double fraction);
        void setObject(const Object& object);
        void setString(const std::string& string);
        void setArray(const Array& array);

        Type type;

        union Storage {
            int* number;
            bool boolean;
            double* fraction;
            Object* object;
            std::string* string;
            Array* array;
        };

        Storage storage;

    };

}


#endif //JSONMAX_JSONELEMENT_H
