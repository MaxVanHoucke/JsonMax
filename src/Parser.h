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
    class Parser {
    public:

        static std::string fileToString(const std::string& fileName);

        /// Finds the position of the next symbol given that is not in a json string
        static int findIndex(size_t start, char symbol, const std::string &string);

        static int findArrayEnding(size_t start, const std::string& string);

        static int findObjectEnding(size_t start, const std::string& string);

        /// When giving '{' it finds the next '}' and returns the position
        static int findEnding(size_t start, char symbol, const std::string &string);

        /// Checks if it's a valid json string
        static bool isValidString(const std::string &string);

        /// Checks if it's a valid json number
        static bool isValidNumber(const std::string &number);

        /// Trims the string, removes whitespace etc
        static std::string trim(const std::string &string);

        /// Parses an object without the { and }
        static Object parseObject(const std::string &object);

        /// Parses an array without the [ and ]
        static Element parseArray(const std::string &array);

        static Element parseArrayContent(const std::string& array);

        static Object parseObjectContent(const std::string& object);

        static Element parseNumber(const std::string& number);

        static Element parseNumberFromString(const std::string& number);

        static Element parseString(const std::string& string);

    };

}



#endif //JSONMAX_JSONPARSER_H
