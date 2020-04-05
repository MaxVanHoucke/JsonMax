/**
 * @author Max Van Houcke
 */

#include "../catch.hpp"
#include "../../src/json_max/parser/Parser.h"

using namespace JsonMax;

TEST_CASE( "Happy days parsing file", "[parsing]" ) {

    Object obj = parseFile("../../test/input/correct.json").getObject();

    CHECK(obj["string"].getString() == "string");
    CHECK(obj["number"].getInt() == 1);
    CHECK(obj["float"].getDouble() == Approx(3.14));
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
            CHECK(element.getDouble() == Approx(3.14));
        }
        else if (element.isString()) {
            CHECK(element.getString() == "string");
        }
        else if (element.isArray()) {
            CHECK(element.getArray()[0].getString() == "another array");
        }
    }
}

TEST_CASE( "Happy days parsing strings", "[parsing]" ) {
    std::vector<std::string> cases {
        "",
        "{}",
        "[]",
        "  [{}] ",

    };

    for (const auto& c : cases) {
        CHECK_NOTHROW(c);
    }
}
