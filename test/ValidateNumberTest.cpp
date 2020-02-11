/**
 * @author Max Van Houcke
 */

#include "catch.hpp"
#include "../src/Parser.h"

using namespace JsonMax;

TEST_CASE( "Numbers are validated", "[Parser::validateNumber]" ) {

    CHECK(Parser::isValidNumber("0"));
    CHECK(Parser::isValidNumber("-0"));
    CHECK(Parser::isValidNumber("0.1"));
    CHECK(Parser::isValidNumber("0.12324"));
    CHECK(Parser::isValidNumber("-0.1"));
    CHECK(Parser::isValidNumber("-0.12324"));
    CHECK(Parser::isValidNumber("0.1e1"));
    CHECK(Parser::isValidNumber("0.11e1"));
    CHECK(Parser::isValidNumber("0.1324e1243"));
    CHECK(Parser::isValidNumber("0.1E1"));
    CHECK(Parser::isValidNumber("0.1324E1243"));
    CHECK(Parser::isValidNumber("0.1e-1"));
    CHECK(Parser::isValidNumber("0.11e+1"));
    CHECK(Parser::isValidNumber("0.1324e-1243"));
    CHECK(Parser::isValidNumber("0.1E+1"));
    CHECK(Parser::isValidNumber("0.1324E-1243"));
    CHECK(Parser::isValidNumber("-0.11e1"));
    CHECK(Parser::isValidNumber("-0.1324e1243"));
    CHECK(Parser::isValidNumber("-0.1E1"));
    CHECK(Parser::isValidNumber("-0.1324E1243"));
    CHECK(Parser::isValidNumber("-0.1e-1"));
    CHECK(Parser::isValidNumber("-0.11e+1"));
    CHECK(Parser::isValidNumber("-0.1324e-1243"));
    CHECK(Parser::isValidNumber("-0.1E+1"));
    CHECK(Parser::isValidNumber("-0.1324E-1243"));

    CHECK(Parser::isValidNumber("1"));
    CHECK(Parser::isValidNumber("-2"));
    CHECK(Parser::isValidNumber("123.1"));
    CHECK(Parser::isValidNumber("1.12324"));
    CHECK(Parser::isValidNumber("-2342.1"));
    CHECK(Parser::isValidNumber("-242.12324"));
    CHECK(Parser::isValidNumber("234.1e1"));
    CHECK(Parser::isValidNumber("2342.11e1"));
    CHECK(Parser::isValidNumber("46.1324e1243"));
    CHECK(Parser::isValidNumber("5.1E1"));
    CHECK(Parser::isValidNumber("64.1324E1243"));
    CHECK(Parser::isValidNumber("46.1e-1"));
    CHECK(Parser::isValidNumber("467.11e+1"));
    CHECK(Parser::isValidNumber("563.1324e-1243"));
    CHECK(Parser::isValidNumber("3546.1E+1"));
    CHECK(Parser::isValidNumber("467.1324E-1243"));
    CHECK(Parser::isValidNumber("-646.11e1"));
    CHECK(Parser::isValidNumber("-463.1324e1243"));
    CHECK(Parser::isValidNumber("-567.1E1"));
    CHECK(Parser::isValidNumber("-35.1324E1243"));
    CHECK(Parser::isValidNumber("-4657353535.1e-1"));
    CHECK(Parser::isValidNumber("-35.11e+1"));
    CHECK(Parser::isValidNumber("-3.1324e-1243"));
    CHECK(Parser::isValidNumber("-3546434.1E+1"));
    CHECK(Parser::isValidNumber("-454643.1324E-1243"));


}


TEST_CASE( "Incorrect numbers are validated", "[Parser::validateNumber]" ) {

    CHECK_FALSE(Parser::isValidNumber("-"));
    CHECK_FALSE(Parser::isValidNumber("--3"));
    CHECK_FALSE(Parser::isValidNumber("dfa"));
    CHECK_FALSE(Parser::isValidNumber("-1a"));
    CHECK_FALSE(Parser::isValidNumber("011"));
    CHECK_FALSE(Parser::isValidNumber("43-13"));
    CHECK_FALSE(Parser::isValidNumber("0."));
    CHECK_FALSE(Parser::isValidNumber("-0.e"));
    CHECK_FALSE(Parser::isValidNumber("12.13e"));
    CHECK_FALSE(Parser::isValidNumber("0.1e"));
    CHECK_FALSE(Parser::isValidNumber("0.1e"));
    CHECK_FALSE(Parser::isValidNumber("0.1ee"));
    CHECK_FALSE(Parser::isValidNumber("0.1ea"));
    CHECK_FALSE(Parser::isValidNumber("."));
    CHECK_FALSE(Parser::isValidNumber("-."));
    CHECK_FALSE(Parser::isValidNumber("-e"));
    CHECK_FALSE(Parser::isValidNumber("-01.13"));
    CHECK_FALSE(Parser::isValidNumber("-01.e="));
    CHECK_FALSE(Parser::isValidNumber("test"));

}
