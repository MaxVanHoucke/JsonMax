/**
 * @author Max Van Houcke
 */

#include "../catch.hpp"
#include "../../src/json_max/parser/Parser.h"
#include "../../src/json_max/parser/ParseException.h"

using namespace JsonMax;

void test(const std::vector<std::string>& cases) {
    for (const auto& c : cases) {
        CHECK_THROWS_AS(parse(c), ParseException);
    }
}

TEST_CASE( "Nightmare parsing objects from strings", "[parsing]" ) {
    std::vector<std::string> cases = {
            "{",
            "}",
            R"(  {   )",
            "]",
            "\"ab",
    };
    test(cases);
}


TEST_CASE( "Nightmare parsing arrays from strings", "[parsing]" ) {
    std::vector<std::string> cases = {
            "{",
            "}",
            "[",
            "]",
            "\"ab",
    };
    test(cases);
}
