/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

#include <iostream>
#include <stack>
#include "Element.h"
#include "Object.h"

namespace JsonMax {

    /**
     * Parses a given string into a json element (object, array, int,...)
     * @param json string
     * @return JSON Element, use appropriate getter to get the value
     */
    Element parse(const std::string& json);

    /**
     * @param fileName the name of the file
     * @return JSON Element parsed from file
     */
    Element parseFile(const std::string& fileName);

    /// Helper function for parsing
    namespace Parser {

        /// Finds the position of the next symbol given that is not in a json string
        int findIndex(size_t start, char symbol, const std::string &string);

        /// When giving '{' it finds the next '}' and returns the position
        int findEnding(size_t start, char symbol, const std::string &string);

        /// Checks if it's a valid json string
        bool validateString(const std::string &string);

        /// Checks if it's a valid json number
        bool validateNumber(const std::string &number);

        /// Trims the string, removes whitespace etc
        std::string trim(const std::string &string);

        /// Parses an object without the { and }
        Object parseObject(const std::string &object);

        /// Parses an array without the [ and ]
        Element parseArray(const std::string &array);

    };

}



#endif //JSONMAX_JSONPARSER_H
