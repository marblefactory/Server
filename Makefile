CC     = g++
CFLAGS = -std=c++11 -w
LINKER = -lboost_system -lpthread

# Directories
SRC_DIR  = src
TEST_DIR = test
BIN_DIR  = bin
EXEC     = $(BIN_DIR)/server

# Actions

# JSON
JSON_DIR        = $(SRC_DIR)/json
JSON_HELPER     = $(JSON_DIR)/json_helper.cpp
ACTION_PARSER   = $(JSON_DIR)/action_parser.cpp
LOCATION_PARSER = $(JSON_DIR)/location_parser.cpp
OBJECT_PARSER   = $(JSON_DIR)/object_parser.cpp
JSON_SRC        = $(JSON_HELPER) $(ACTION_PARSER) $(LOCATION_PARSER) $(OBJECT_PARSER)

# Locations
# Objects

# Server
SERVER = $(SRC_DIR)/server/server.cpp

SRC  = $(JSON_SRC) $(SERVER)
MAIN = $(SRC) $(SRC_DIR)/main.cpp

# Testing
	# Actions
TEST_ACTION_VISITOR = $(TEST_DIR)/actions/test_action_visitor.cpp
TEST_ACTIONS        = $(TEST_ACTION_VISITOR)

	# Locations
TEST_LOCATION_VISITOR = $(TEST_DIR)/locations/test_location_visitor.cpp
TEST_LOCATIONS 	      = $(TEST_LOCATION_VISITOR)

	# JSON Parsing
TEST_OBJECT_PARSER   = $(TEST_DIR)/json/test_object_parser.cpp
TEST_ACTION_PARSER   = $(TEST_DIR)/json/test_action_parser.cpp
TEST_LOCATION_PARSER = $(TEST_DIR)/json/test_location_parser.cpp
TEST_PARSER 		 = $(TEST_OBJECT_PARSER) $(TEST_ACTION_PARSER) $(TEST_LOCATION_PARSER)

TESTING_MAIN = $(SRC) $(TEST_ACTIONS) $(TEST_LOCATIONS) $(TEST_PARSER) $(TEST_DIR)/main.cpp

# default:
# 	$(CC) $(CFLAGS) $(MAIN) -o $(EXEC) $(LINKER)

default:
	$(CC) $(CFLAGS) $(TESTING_MAIN) -o $(EXEC) $(LINKER)

clean:
	rm $(BIN_DIR)/*
