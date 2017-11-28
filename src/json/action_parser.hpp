//
//  action_parser.hpp
//  EngineCommandSet
//
//  Created by Albie Baker-Smith on 17/11/2017.
//  Copyright © 2017 Albie Baker-Smith. All rights reserved.
//

#ifndef action_parser_hpp
#define action_parser_hpp

#include "../../libs/json.hpp"
#include "../objects/object.hpp"
#include "../actions/action.hpp"

using nlohmann::json;
using std::exception;

namespace json_parsing {
    // Parses an Action, throws if parsing was unsuccessful.
    Action *parse_action(json j) throw(exception);
}

#endif /* action_parser_hpp */
