/**
 * @author Max Van Houcke
 */

#include "catch.hpp"
#include "../src/Parser.h"

using namespace JsonMax::Parser;

TEST_CASE( "Strings are validated", "[validateString]" ) {

    CHECK(validateString(""));
    CHECK(validateString(" "));
    CHECK(validateString("test a b c d e f g"));
    CHECK(validateString("test abcdefg test"));
    CHECK(validateString("hello world"));
    CHECK(validateString("\\\" yes "));
    CHECK(validateString("\\\" yes \\\""));
    CHECK(validateString("\\/"));
    CHECK(validateString("\\b"));
    CHECK(validateString("\\f"));
    CHECK(validateString("\\n"));
    CHECK(validateString("\\r"));
    CHECK(validateString("\\t"));
    CHECK(validateString("\\uabcd"));
    CHECK(validateString("\\uabcd"));
    CHECK(validateString("\\u123d"));
    CHECK(validateString("\\u123d"));
    CHECK(validateString("\\u01fd"));
    CHECK(validateString("\\u0abc"));

}

TEST_CASE( "Incorrect strings are validated", "[validateString]" ) {

    CHECK_FALSE(validateString("\""));
    CHECK_FALSE(validateString("\\u123"));
    CHECK_FALSE(validateString("\\u12he"));
    CHECK_FALSE(validateString("\\a"));
    CHECK_FALSE(validateString("\\c"));
    CHECK_FALSE(validateString("\\g"));
    CHECK_FALSE(validateString("\"  \""));

}