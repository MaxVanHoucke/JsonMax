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

    class JsonElement {
    public:

        friend std::ostream &operator<<(std::ostream &out, const JsonElement &element);

        /**
         * Constructors
         */

        JsonElement();
        JsonElement(const std::string &string);
        JsonElement(const char *old_string);
        JsonElement(int num);
        JsonElement(double fraction);
        JsonElement(bool boolean);
        JsonElement(const Object &obj);
        JsonElement(const std::vector<JsonElement> &arr);
        JsonElement(const std::initializer_list<JsonElement> &arr);
        JsonElement(std::nullptr_t pointer);

        Type getType() const;
        JsonElement &operator[](const char *c_string);
        std::string toString(unsigned int indent = 0) const;

        /**
         * Operator=
         */

        JsonElement &operator=(const std::string &string);
        JsonElement &operator=(const char *c_string);
        JsonElement &operator=(int num);
        JsonElement &operator=(double fract);
        JsonElement &operator=(bool boolean);
        JsonElement &operator=(const Object &obj);
        JsonElement &operator=(const std::vector<JsonElement> &arr);
        JsonElement &operator=(const std::initializer_list<JsonElement> &arr);
        JsonElement &operator=(std::nullptr_t pointer);

        /**
         * Type operators
         */

        operator int() const;
        operator bool() const;
        operator double() const;
        operator Object() const;
        operator std::string() const;
        operator const char *() const;
        operator std::vector<JsonElement>() const;

    private:

        void checkType(Type castType) const;

        void setNumber(int number);
        void setBoolean(bool boolean);
        void setFraction(double fraction);
        void setObject(Object object);
        void setString(const std::string &string);
        void setArray(const std::vector<JsonElement> &array);

        Type type;

        int number;
        bool boolean;
        double fraction;
        Object *object;
        std::string string;
        std::vector<JsonElement> array;

    };

}

/**
 * Output stream operator for a json element
 * @return
 */
std::ostream &operator<<(std::ostream &, const JsonMax::JsonElement &);


#endif //JSONMAX_JSONELEMENT_H
