# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -g

# Project directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target: build the project
all: $(BIN_DIR)/mylang

# Link the object files to create the executable
$(BIN_DIR)/mylang: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(BIN_DIR)/mylang $(CXXFLAGS)

# Compile individual source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean the build files
clean:
	rm -rf $(OBJ_DIR)/** $(BIN_DIR)/**

.PHONY: all clean
