/**
 * @author Max Van Houcke
 */

#ifndef JSONMAX_JSONPARSER_H
#define JSONMAX_JSONPARSER_H

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


    /**
     * Main Parser class
     * Can parse any JSON string.
     * Base class for all other parsers such as ObjectParser etc
     */
    class Parser {
    public:

        /// Constructor, stores the reference of a JSON string
        explicit Parser(const std::string& str) : Parser(str, 0, str.size()) {}

        /// Constructor, takes JSON but also the start and end positions (end position is not including)
        Parser(const std::string& str, size_t start, size_t end) : json(str), index(start), endIndex(end) {}

        /// Parses the stored json
        virtual Element parse();

    protected:

        /**
         *  Returns true if end of parsing is reached
         *  This also includes being positioned on the last char of the json
         */
        bool endOfParsing() const;

        /**
         * Finds the given symbol in the json, starting from the current position
         * Skips any element such as an object, array or string
         * @return the index of the symbol
         */
        size_t findIndexAfterElement(char symbol);

        /// Returns the stored json
        const std::string& getJson() const;

        /// Remaining characters in the json, includes the current position
        size_t remainingSize() const;

        /// Returns the current position/index
        size_t currentPosition() const;

        /// Returns the char in the json at the current position
        char currentSymbol() const;

        /// Returns the last position/index (which is still part of the json)
        size_t lastPosition() const;

        /// Incrementer for the position
        void incrementPosition();

        /// Setter for the position
        void setPosition(size_t pos);

        /// Trims any whitespace at the end by adjusting the endIndex/lastPosition
        void trimEndWhitespace();

        /// Moves the position to the first element that is not whitespace
        void moveToNonEmptyPosition();

        /// Trims the whitespace around the element
        void trim();

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
