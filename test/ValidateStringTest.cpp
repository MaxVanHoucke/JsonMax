/**
 * @author Max Van Houcke
 */

#include <gtest/gtest.h>
#include "../include/Parser.h"

TEST(validateString, happyDay) {

    EXPECT_TRUE(JsonParser::validateString(""));
    EXPECT_TRUE(JsonParser::validateString(" "));
    EXPECT_TRUE(JsonParser::validateString("test a b c d e f g"));
    EXPECT_TRUE(JsonParser::validateString("test abcdefg test"));
    EXPECT_TRUE(JsonParser::validateString("hello world"));
    EXPECT_TRUE(JsonParser::validateString("\\\" yes "));
    EXPECT_TRUE(JsonParser::validateString("\\\" yes \\\""));
    EXPECT_TRUE(JsonParser::validateString("\\/"));
    EXPECT_TRUE(JsonParser::validateString("\\b"));
    EXPECT_TRUE(JsonParser::validateString("\\f"));
    EXPECT_TRUE(JsonParser::validateString("\\n"));
    EXPECT_TRUE(JsonParser::validateString("\\r"));
    EXPECT_TRUE(JsonParser::validateString("\\t"));
    EXPECT_TRUE(JsonParser::validateString("\\uabcd"));
    EXPECT_TRUE(JsonParser::validateString("\\uabcd"));
    EXPECT_TRUE(JsonParser::validateString("\\u123d"));
    EXPECT_TRUE(JsonParser::validateString("\\u123d"));
    EXPECT_TRUE(JsonParser::validateString("\\u01fd"));
    EXPECT_TRUE(JsonParser::validateString("\\u0abc"));

}

TEST(validateString, invalid) {

    EXPECT_FALSE(JsonParser::validateString("\""));
    EXPECT_FALSE(JsonParser::validateString("\\u123"));
    EXPECT_FALSE(JsonParser::validateString("\\u12he"));
    EXPECT_FALSE(JsonParser::validateString("\\a"));
    EXPECT_FALSE(JsonParser::validateString("\\c"));
    EXPECT_FALSE(JsonParser::validateString("\\g"));
    EXPECT_FALSE(JsonParser::validateString("\"  \""));

}