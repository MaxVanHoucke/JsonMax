/**
 * @author Max Van Houcke
 */

#include <iostream>

#include "Parser.h"
#include "ObjectParser.h"
#include "ArrayParser.h"
#include "StringParser.h"
#include "NumberParser.h"

#include "Utils.h"

using namespace JsonMax;

Element JsonMax::parse(const std::string &json) {
    return Parser(json).parse();
}

Element JsonMax::parseFile(const std::string &fileName) {
    std::string fileContent = Utils::fileToString(fileName);
    return parse(fileContent);
}

Element Parser::parse() {
    trim();
    size_t size = remainingSize();

    if (size == 0) {
        return Element();
    } else if (size == 4 and json.substr(index, size) == "true") {
        return Element(true);
    } else if (size == 5 and json.substr(index, size) == "false") {
        return Element(false);
    } else if (size == 4 and json.substr(index, size) == "null") {
        return Element(nullptr);
    } else if (currentSymbol() == '{') {
        return ObjectParser(json, index, endIndex).parse();
    } else if (currentSymbol() == '[') {
        return ArrayParser(json, index, endIndex).parse();
    } else if (currentSymbol() == '"') {
        return StringParser(json, index, endIndex).parse();
    } else {
        return NumberParser(json, index, endIndex).parse();
    }
}

void Parser::moveToNonEmptyPosition() {
    index = json.find_first_not_of(" \t\n", index);
    if (index == std::string::npos) {
        index = endIndex;
    }
}


void Parser::trim() {
    moveToNonEmptyPosition();
    trimEndWhitespace();
}


bool Parser::endOfParsing() const {
    return index == std::string::npos or index >= endIndex - 1;
}

void Parser::trimEndWhitespace() {
    endIndex = getJson().find_last_not_of(" \t\n", lastPosition());
    if (endIndex == std::string::npos) {
        endIndex = index;
    } else {
        endIndex++;
    }
}

size_t Parser::findIndexAfterElement(char symbol) {
    bool skip = false;
    bool inString = false;

    int arrayCounter = 0;
    int objectCounter = 0;
    for (size_t i = index; i <= lastPosition(); i++) {
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

    return std::string::npos;
}

size_t Parser::remainingSize() const {
    return endIndex - index;
}

const std::string& Parser::getJson() const {
    return json;
}

size_t Parser::currentPosition() const {
    return index;
}

size_t Parser::lastPosition() const {
    return endIndex - 1;
}

void Parser::incrementPosition() {
    index++;
}

void Parser::setPosition(size_t pos) {
    index = pos;
}

char Parser::currentSymbol() const {
    return getJson().at(currentPosition());
}

void Parser::throwException(const std::string &msg) const {
    throw ParseException(msg, getJson(), currentPosition());
}
