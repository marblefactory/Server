//
//  test_action_visitor.cpp
//  EngineCommandSet
//
//  Created by Albie Baker-Smith on 14/11/2017.
//  Copyright © 2017 Albie Baker-Smith. All rights reserved.
//

#include "../../libs/catch.hpp"
#include "../../src/actions/action.hpp"

// Used for testing. Stores the location it last visited.
class MockActionVisitor: public ActionVisitor {
public:
    Action *visited_action = nullptr;

    void visit(Move &move) override {
        this->visited_action = &move;
    }
};

SCENARIO("Visiting Movements") {
    AbsoluteLocation loc;
    Object obj("Table", &loc);
    Move move(&obj);

    MockActionVisitor visitor;

    move.accept(visitor);

    REQUIRE(visitor.visited_action == &move);
}
