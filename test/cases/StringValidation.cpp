/**
 * @author Max Van Houcke
 */

#include "../catch.hpp"
#include "../../src/json_max/parser/Parser.h"

using namespace JsonMax;

TEST_CASE( "Strings are validated", "[validateString]" ) {

    CHECK_NOTHROW(Parser("\"\"").parse());
    CHECK_NOTHROW(Parser("\" \"").parse());
    CHECK_NOTHROW(Parser("\"test a b c d e f g\"").parse());
    CHECK_NOTHROW(Parser("\"test abcdefg test\"").parse());
    CHECK_NOTHROW(Parser("\"hello world\"").parse());
    CHECK_NOTHROW(Parser("\"\\\" yes \"").parse());
    CHECK_NOTHROW(Parser("\"\\\" yes \\\"\"").parse());
    CHECK_NOTHROW(Parser("\"\\/\"").parse());
    CHECK_NOTHROW(Parser("\"\\b\"").parse());
    CHECK_NOTHROW(Parser("\"\\f\"").parse());
    CHECK_NOTHROW(Parser("\"\\n\"").parse());
    CHECK_NOTHROW(Parser("\"\\r\"").parse());
    CHECK_NOTHROW(Parser("\"\\t\"").parse());
    CHECK_NOTHROW(Parser("\"\\uabcd\"").parse());
    CHECK_NOTHROW(Parser("\"\\uabcd\"").parse());
    CHECK_NOTHROW(Parser("\"\\u123d\"").parse());
    CHECK_NOTHROW(Parser("\"\\u123d\"").parse());
    CHECK_NOTHROW(Parser("\"\\u01fd\"").parse());
    CHECK_NOTHROW(Parser("\"\\u0abc\"").parse());

}

TEST_CASE( "Incorrect strings are validated", "[validateString]" ) {

    CHECK_THROWS(Parser("\"").parse());
    CHECK_THROWS(Parser("\"\"\"").parse());
    CHECK_THROWS(Parser("\\u123").parse());
    CHECK_THROWS(Parser("\\u12he").parse());
    CHECK_THROWS(Parser("\\a").parse());
    CHECK_THROWS(Parser("\\c").parse());
    CHECK_THROWS(Parser("\\g").parse());

}
