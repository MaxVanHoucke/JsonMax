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

        explicit Parser(const std::string& str) : Parser(str, 0, str.size() - 1) {}

        Parser(const std::string& str, size_t start, size_t end) : json(str), index(start), endIndex(end) {}

        virtual Element parse();


    protected:

        bool endOfParsing() const;

        std::string extractElementAndAdjustIndex();

        size_t findIndexAfterElement(char symbol);

        const std::string& getJson() const;

        size_t remainingSize() const;

        size_t currentPosition() const;

        char currentSymbol() const;

        size_t lastPosition() const;

        void incrementPosition();

        void setPosition(size_t pos);

        void trim();

        void trimEndWhitespace();

        void moveToNonEmptyPosition();

    private:

        /// Reference to the json string parsed
        const std::string& json;

        /// Current index in the json
        size_t index;

        /// One after the last index of the json
        size_t endIndex;

    };

}



#endif //JSONMAX_JSONPARSER_H
