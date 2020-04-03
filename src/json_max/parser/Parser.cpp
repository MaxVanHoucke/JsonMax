/**
 * @author Max Van Houcke
 */

#include "Parser.h"
#include "../Exceptions.h"
#include "ObjectParser.h"
#include "ArrayParser.h"
#include "StringParser.h"
#include "NumberParser.h"

#include <fstream>
#include <sstream>

using namespace JsonMax;

Element JsonMax::parse(const std::string &json) {
    return Parser(json).parse();
}

Element JsonMax::parseFile(const std::string &fileName) {
    std::string fileContent = Parser::fileToString(fileName);
    return parse(fileContent);
}

Element Parser::parse() {
    trimEndWhitespace();
    moveToNonEmptyPosition();
    size_t size = endIndex - index;

    if (size == 0) {
        return Element();
    } else if (size == 4 and json.substr(index, size) == "true") {
        return Element(true);
    } else if (size == 5 and json.substr(index, size) == "false") {
        return Element(false);
    } else if (size == 5 and json.substr(index, size) == "null") {
        return Element(nullptr);
    } else if (json[index] == '{') {
        return ObjectParser(json, index, endIndex).parse();
    } else if (json[index] == '[') {
        return ArrayParser(json, index, endIndex).parse();
    } else if (json[index] == '"') {
        return StringParser(json, index, endIndex).parse();
    } else {
        return NumberParser(json, index, endIndex).parse();
    }
}

void Parser::moveToNonEmptyPosition() {
    index = json.find_first_not_of(" \t\n", index);
}


void Parser::trim() {
    trimEndWhitespace();
    moveToNonEmptyPosition();
}


bool Parser::endOfParsing() const {
    return index == std::string::npos or index >= endIndex;
}

std::string Parser::fileToString(const std::string &fileName) {
    std::ifstream in(fileName);
    if (not in.good()) {
        throw ParseException("Couldn't open " + fileName);
    }
    std::ostringstream stream;
    stream << in.rdbuf();
    return stream.str();
}

std::string Parser::extractElementAndAdjustIndex() {
    moveToNonEmptyPosition();
    size_t indexOfNextComma = findIndexAfterElement(',');
    std::string element = json.substr(index, indexOfNextComma - index);
    if (indexOfNextComma == std::string::npos) {
        index = std::string::npos;
    } else {
        index = indexOfNextComma + 1;
    }
    return element;
}

void Parser::trimEndWhitespace() {
    endIndex = json.find_last_not_of(" \t\n", index, endIndex - index);
}

size_t Parser::findIndexAfterElement(char symbol) {
    bool skip = false;
    bool inString = false;

    int arrayCounter = 0;
    int objectCounter = 0;
    for (size_t i = index; i < json.size(); i++) {
        char current = json[i];

        if (skip) {
            skip = false;
            continue;
        } else if (inString) {
            inString = current != '"';
            continue;
        }

        if (current == symbol and objectCounter == 0 and arrayCounter == 0) {
            return i;
        }

        if (current == '\\') {
            skip = true;
        } else if (current == '"') {
            inString = true;
        } else if (current == '{') {
            objectCounter++;
        } else if (current == '}') {
            objectCounter--;
        } else if (current == '[') {
            arrayCounter++;
        } else if (current == ']') {
            arrayCounter--;
        }
    }

    return -1;
}
