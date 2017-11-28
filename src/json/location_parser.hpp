//
//  location_parser.hpp
//  EngineCommandSet
//
//  Created by Albie Baker-Smith on 17/11/2017.
//  Copyright © 2017 Albie Baker-Smith. All rights reserved.
//

#ifndef location_parser_hpp
#define location_parser_hpp

#include "../locations/locations.hpp"
#include "../../libs/json.hpp"

using nlohmann::json;
using std::exception;

namespace json_parsing {
    // Returns a parsed Location, or an throws if parsing was unsuccessful.
    Location* parse_location(json j) throw(exception);
}

#endif /* location_parser_hpp */
