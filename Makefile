# Project name
PROJECTNAME = program

# Output directory
OUTPUT_DIR = build

# Include directories
INCLUDE_DIRS = -Iinclude/SDL2 -Iinclude/imgui

# Library directories
LIB_DIRS = -Llib

# Libraries to link against
LIBS = -lmingw32 -lSDL2main -lSDL2

# Source files
SRC = $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)

# Compiler
CXX = g++

# Default target
default: $(OUTPUT_DIR)/$(PROJECTNAME)

# Build the program
$(OUTPUT_DIR)/$(PROJECTNAME): $(SRC)
	if not exist $(OUTPUT_DIR) mkdir $(OUTPUT_DIR)
	$(CXX) $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)

# Clean up build files
clean:
	if exist $(OUTPUT_DIR) rmdir /S /Q $(OUTPUT_DIR)