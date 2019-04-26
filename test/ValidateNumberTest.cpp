/**
 * @author Max Van Houcke
 */

#include "catch.h"
#include "../src/Parser.h"

using namespace JsonMax::Parser;

TEST_CASE( "Numbers are validated", "[validateNumber]" ) {
    REQUIRE( validateNumber("0") );
}


//#include <gtest/gtest.h>
//#include "../src/Parser.h"
//
//
//TEST(validateNumber, happyDay) {
//
//    EXPECT_TRUE(JsonParser::validateNumber("0"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.12324"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.12324"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1e1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.11e1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1324e1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1E1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1324E1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1e-1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.11e+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1324e-1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1E+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("0.1324E-1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.11e1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1324e1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1E1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1324E1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1e-1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.11e+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1324e-1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1E+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-0.1324E-1243"));
//
//    EXPECT_TRUE(JsonParser::validateNumber("1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-2"));
//    EXPECT_TRUE(JsonParser::validateNumber("123.1"));
//    EXPECT_TRUE(JsonParser::validateNumber("1.12324"));
//    EXPECT_TRUE(JsonParser::validateNumber("-2342.1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-242.12324"));
//    EXPECT_TRUE(JsonParser::validateNumber("234.1e1"));
//    EXPECT_TRUE(JsonParser::validateNumber("2342.11e1"));
//    EXPECT_TRUE(JsonParser::validateNumber("46.1324e1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("5.1E1"));
//    EXPECT_TRUE(JsonParser::validateNumber("64.1324E1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("46.1e-1"));
//    EXPECT_TRUE(JsonParser::validateNumber("467.11e+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("563.1324e-1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("3546.1E+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("467.1324E-1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-646.11e1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-463.1324e1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-567.1E1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-35.1324E1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-4657353535.1e-1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-35.11e+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-3.1324e-1243"));
//    EXPECT_TRUE(JsonParser::validateNumber("-3546434.1E+1"));
//    EXPECT_TRUE(JsonParser::validateNumber("-454643.1324E-1243"));
//
//
//}
//
//TEST(validateNumber, invalid) {
//
//    EXPECT_FALSE(JsonParser::validateNumber("-"));
//    EXPECT_FALSE(JsonParser::validateNumber("dfa"));
//    EXPECT_FALSE(JsonParser::validateNumber("-1a"));
//    EXPECT_FALSE(JsonParser::validateNumber("011"));
//    EXPECT_FALSE(JsonParser::validateNumber("43-13"));
//    EXPECT_FALSE(JsonParser::validateNumber("0."));
//    EXPECT_FALSE(JsonParser::validateNumber("-0.e"));
//    EXPECT_FALSE(JsonParser::validateNumber("12.13e"));
//    EXPECT_FALSE(JsonParser::validateNumber("0.1e"));
//    EXPECT_FALSE(JsonParser::validateNumber("0.1e"));
//    EXPECT_FALSE(JsonParser::validateNumber("0.1ee"));
//    EXPECT_FALSE(JsonParser::validateNumber("0.1ea"));
//    EXPECT_FALSE(JsonParser::validateNumber("."));
//    EXPECT_FALSE(JsonParser::validateNumber("-."));
//    EXPECT_FALSE(JsonParser::validateNumber("-e"));
//    EXPECT_FALSE(JsonParser::validateNumber("-01.13"));
//    EXPECT_FALSE(JsonParser::validateNumber("-01.e="));
//    EXPECT_FALSE(JsonParser::validateNumber("test"));
//
//}