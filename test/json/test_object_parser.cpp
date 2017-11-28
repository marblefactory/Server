//
//  test_object_parser.cpp
//  EngineCommandSet
//
//  Created by Albie Baker-Smith on 17/11/2017.
//  Copyright © 2017 Albie Baker-Smith. All rights reserved.
//

#include "../../libs/catch.hpp"
#include "../../libs/json.hpp"
#include "../../src/json/object_parser.hpp"

using namespace json_parsing;

SCENARIO("Parsing Objects") {
    GIVEN("Valid JSON") {
        json j = {
            {"name", "door"},
            {"location", {
                {"type", "absolute"}
            }}
        };

        Object *obj = parse_object(j);
        AbsoluteLocation *loc = (AbsoluteLocation*)obj->location;

        REQUIRE(obj->name == "door");
    }

    GIVEN("JSON where the name is missing") {
        THEN("an exception is thrown") {
            json j = {
                {"location", {
                    {"type", "absolute"}
                }}
            };

            REQUIRE_THROWS(parse_object(j));
        }
    }
}
