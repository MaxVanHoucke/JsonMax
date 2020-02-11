/**
 * @author Max Van Houcke
 */

#include "catch.hpp"
#include "../src/Parser.h"

using namespace JsonMax;

TEST_CASE( "Strings are validated", "[validateString]" ) {

    CHECK(Parser::isValidString("\"\""));
    CHECK(Parser::isValidString("\" \""));
    CHECK(Parser::isValidString("\"test a b c d e f g\""));
    CHECK(Parser::isValidString("\"test abcdefg test\""));
    CHECK(Parser::isValidString("\"hello world\""));
    CHECK(Parser::isValidString("\"\\\" yes \""));
    CHECK(Parser::isValidString("\"\\\" yes \\\"\""));
    CHECK(Parser::isValidString("\"\\/\""));
    CHECK(Parser::isValidString("\"\\b\""));
    CHECK(Parser::isValidString("\"\\f\""));
    CHECK(Parser::isValidString("\"\\n\""));
    CHECK(Parser::isValidString("\"\\r\""));
    CHECK(Parser::isValidString("\"\\t\""));
    CHECK(Parser::isValidString("\"\\uabcd\""));
    CHECK(Parser::isValidString("\"\\uabcd\""));
    CHECK(Parser::isValidString("\"\\u123d\""));
    CHECK(Parser::isValidString("\"\\u123d\""));
    CHECK(Parser::isValidString("\"\\u01fd\""));
    CHECK(Parser::isValidString("\"\\u0abc\""));

}

TEST_CASE( "Incorrect strings are validated", "[validateString]" ) {

    CHECK_FALSE(Parser::isValidString("\""));
    CHECK_FALSE(Parser::isValidString("\"\"\""));
    CHECK_FALSE(Parser::isValidString("\\u123"));
    CHECK_FALSE(Parser::isValidString("\\u12he"));
    CHECK_FALSE(Parser::isValidString("\\a"));
    CHECK_FALSE(Parser::isValidString("\\c"));
    CHECK_FALSE(Parser::isValidString("\\g"));

}