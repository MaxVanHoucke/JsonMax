/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

#include <stack>
#include "../model/Element.h"
#include "../model/Object.h"

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


    class Parser {
    public:

        Parser(const std::string& str, size_t start, size_t end) : json(str), index(start), endIndex(end) {}

        explicit Parser(const std::string& str) : json(str), index(0), endIndex(str.size()) {}

        virtual Element parse();

        static std::string fileToString(const std::string& fileName);

    protected:


        bool endOfParsing() const;

        std::string extractElementAndAdjustIndex();

        size_t findIndexAfterElement(char symbol);

        void trim();

        void trimEndWhitespace();

        void moveToNonEmptyPosition();

        const std::string& json;
        size_t index;
        size_t endIndex;

    };

}



#endif //JSONMAX_JSONPARSER_H
