/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONELEMENT_H
#define JSONMAX_JSONELEMENT_H

#include <string>
#include <vector>

#include "Iterator.h"
#include "Type.h"

namespace JsonMax {

    class Object;

    class Element {
    public:

        Iterator begin();
        Iterator end();

        Type getType() const;
        Element &operator[](const char *c_string);
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
        Element(const std::vector<Element> &arr);
        Element(const std::initializer_list<Element> &arr);
        Element(std::nullptr_t pointer);

        /**
         * Operator=
         */

        Element &operator=(const std::string &string);
        Element &operator=(const char *c_string);
        Element &operator=(int num);
        Element &operator=(double fract);
        Element &operator=(bool boolean);
        Element &operator=(const Object &obj);
        Element &operator=(const std::vector<Element> &arr);
        Element &operator=(const std::initializer_list<Element> &arr);
        Element &operator=(std::nullptr_t pointer);

        /**
         * Type operators
         */

        operator int() const;
        operator bool() const;
        operator double() const;
        operator Object() const;
        operator std::string() const;
        operator const char *() const;
        operator std::vector<Element>() const;

    private:

        void checkType(Type castType) const;

        void setNumber(int number);
        void setBoolean(bool boolean);
        void setFraction(double fraction);
        void setObject(Object object);
        void setString(const std::string &string);
        void setArray(const std::vector<Element> &array);

        Type type;

        int number;
        bool boolean;
        double fraction;
        Object *object;
        std::string string;
        std::vector<Element> array;

    };

}


#endif //JSONMAX_JSONELEMENT_H
