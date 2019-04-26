/**
 * @author Max Van Houcke
 */

#include "catch.h"
#include "../src/Parser.h"

using namespace JsonMax::Parser;

TEST_CASE( "Numbers are validated", "[validateNumber]" ) {

    CHECK(validateNumber("0"));
    CHECK(validateNumber("-0"));
    CHECK(validateNumber("0.1"));
    CHECK(validateNumber("0.12324"));
    CHECK(validateNumber("-0.1"));
    CHECK(validateNumber("-0.12324"));
    CHECK(validateNumber("0.1e1"));
    CHECK(validateNumber("0.11e1"));
    CHECK(validateNumber("0.1324e1243"));
    CHECK(validateNumber("0.1E1"));
    CHECK(validateNumber("0.1324E1243"));
    CHECK(validateNumber("0.1e-1"));
    CHECK(validateNumber("0.11e+1"));
    CHECK(validateNumber("0.1324e-1243"));
    CHECK(validateNumber("0.1E+1"));
    CHECK(validateNumber("0.1324E-1243"));
    CHECK(validateNumber("-0.11e1"));
    CHECK(validateNumber("-0.1324e1243"));
    CHECK(validateNumber("-0.1E1"));
    CHECK(validateNumber("-0.1324E1243"));
    CHECK(validateNumber("-0.1e-1"));
    CHECK(validateNumber("-0.11e+1"));
    CHECK(validateNumber("-0.1324e-1243"));
    CHECK(validateNumber("-0.1E+1"));
    CHECK(validateNumber("-0.1324E-1243"));

    CHECK(validateNumber("1"));
    CHECK(validateNumber("-2"));
    CHECK(validateNumber("123.1"));
    CHECK(validateNumber("1.12324"));
    CHECK(validateNumber("-2342.1"));
    CHECK(validateNumber("-242.12324"));
    CHECK(validateNumber("234.1e1"));
    CHECK(validateNumber("2342.11e1"));
    CHECK(validateNumber("46.1324e1243"));
    CHECK(validateNumber("5.1E1"));
    CHECK(validateNumber("64.1324E1243"));
    CHECK(validateNumber("46.1e-1"));
    CHECK(validateNumber("467.11e+1"));
    CHECK(validateNumber("563.1324e-1243"));
    CHECK(validateNumber("3546.1E+1"));
    CHECK(validateNumber("467.1324E-1243"));
    CHECK(validateNumber("-646.11e1"));
    CHECK(validateNumber("-463.1324e1243"));
    CHECK(validateNumber("-567.1E1"));
    CHECK(validateNumber("-35.1324E1243"));
    CHECK(validateNumber("-4657353535.1e-1"));
    CHECK(validateNumber("-35.11e+1"));
    CHECK(validateNumber("-3.1324e-1243"));
    CHECK(validateNumber("-3546434.1E+1"));
    CHECK(validateNumber("-454643.1324E-1243"));


}


TEST_CASE( "Incorrect numbers are validated", "[validateNumber]" ) {

    CHECK_FALSE(validateNumber("-"));
    CHECK_FALSE(validateNumber("dfa"));
    CHECK_FALSE(validateNumber("-1a"));
    CHECK_FALSE(validateNumber("011"));
    CHECK_FALSE(validateNumber("43-13"));
    CHECK_FALSE(validateNumber("0."));
    CHECK_FALSE(validateNumber("-0.e"));
    CHECK_FALSE(validateNumber("12.13e"));
    CHECK_FALSE(validateNumber("0.1e"));
    CHECK_FALSE(validateNumber("0.1e"));
    CHECK_FALSE(validateNumber("0.1ee"));
    CHECK_FALSE(validateNumber("0.1ea"));
    CHECK_FALSE(validateNumber("."));
    CHECK_FALSE(validateNumber("-."));
    CHECK_FALSE(validateNumber("-e"));
    CHECK_FALSE(validateNumber("-01.13"));
    CHECK_FALSE(validateNumber("-01.e="));
    CHECK_FALSE(validateNumber("test"));

}
