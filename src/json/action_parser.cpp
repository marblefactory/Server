//
//  action_parser.cpp
//  EngineCommandSet
//
//  Created by Albie Baker-Smith on 17/11/2017.
//  Copyright © 2017 Albie Baker-Smith. All rights reserved.
//

#include "action_parser.hpp"
#include "object_parser.hpp"
#include "json_helper.hpp"

namespace json_parsing {
    // Parses a Move action, or throws if parsing was unsuccessful.
    Move *parse_move(json j) throw(exception) {
        auto dest_json = j["dest"];
        
        if (dest_json.is_null()) {
            throw MissingJsonFieldParseError("destination", "Movement");
        }
        
        Object *dest = parse_object(dest_json);
        
        return new Move(dest);
    }
    
    // Parses an Action, throws if parsing was unsuccessful.
    Action *parse_action(json j) throw(exception) {
        auto type_json = j["type"];
        
        if (type_json.is_null()) {
            throw MissingJsonFieldParseError("type", "Action");
        }
        
        
        string type = type_json.get<string>();
        
        if (type == "move") {
            return parse_move(j);
        }
        
        throw UnknownJsonFieldParseError("type", "Action");
    }
}
