/**
 * @author Max Van Houcke
 */

#include "catch.hpp"
#include "../src/Parser.h"

using namespace JsonMax;

TEST_CASE( "Happy days parsing", "[parsing]" ) {

    Object obj = parseFile("../../test/input/example.json").getObject();

    CHECK(obj["string"].getString() == "string");
    CHECK(obj["number"].getInt() == 1);
    CHECK((obj["float"].getDouble() < 3.15 && obj["float"].getDouble() > 3.13));
    CHECK(obj["null"].isNull());
    CHECK(obj["bool"].getBool());
    CHECK(obj["object"]["object"]["object"]["string"].getString() == "string");
    CHECK(obj["empty object"].getObject().empty());

    for (const Element& element: obj["array"].getArray()) {
        if (element.isObject()) {
            CHECK(element.getObject()["type"].getString() == "object");
        }
        else if (element.isInt()) {
            CHECK(element.getInt() == 1);
        }
        else if (element.isDouble()) {
            CHECK((element.getDouble() < 3.15 && element.getDouble() > 3.13));
        }
        else if (element.isString()) {
            CHECK(element.getString() == "string");
        }
        else if (element.isArray()) {
            CHECK(element.getArray()[0].getString() == "another array");
        }
    }
}
