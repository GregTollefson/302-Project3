# ============================================================
# CS302 Project 3 Makefile
# Music Library (Binary Search Tree)
# ============================================================
#
# This Makefile compiles a multi-file C++ project that uses a
# directory layout to keep source, headers, and build artifacts
# separate:
#
#   project_03/
#   ├── include/          <- Header files (.h)
#   ├── src/              <- Source files (.cpp)
#   ├── build/            <- Compiled objects and executable (generated)
#   └── Makefile
#
# HOW IT WORKS
# ------------
# 1. SRCS lists every .cpp file in src/ that needs to be compiled.
#    When you create a new .cpp file, add it to the SRCS list.
#
# 2. The pattern rule (BUILD_DIR/%.o : SRC_DIR/%.cpp) tells make
#    how to compile any .cpp in src/ into a .o in build/.
#    The -Iinclude flag tells the compiler to look in include/
#    when resolving #include "SomeHeader.h" directives.
#
# 3. The link step combines all .o files into the final executable.
#
# 4. `make clean` removes only build artifacts — your source is safe.
#
# TARGETS
# -------
#   make          Build the executable (default)
#   make run      Build and run the program
#   make clean    Remove all compiled files (build/*.o and the executable)
#
# ============================================================

# --- Compiler and flags ---
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude

# --- Directory layout ---
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# --- Executable name ---
TARGET = project3

# ------------------------------------------------------------
# Source files — list every .cpp that should be compiled.
# Add your .cpp files here as you create them.
# NOTE: Each line except the last must end with a backslash (\).
#
# Example: once you create Song.cpp and MusicLibrary.cpp, update
# this list to look like:
#
#   SRCS = $(SRC_DIR)/driver.cpp \
#          $(SRC_DIR)/Song.cpp \
#          $(SRC_DIR)/MusicLibrary.cpp
#
# BST.h is a header-only template — it does NOT appear here
# because templates are not compiled separately. The compiler
# sees BST.h when it is #included by MusicLibrary.cpp.
# ------------------------------------------------------------
SRCS = $(SRC_DIR)/driver.cpp

# --- Derived variables (you should not need to change these) ---

# Converts each src/Foo.cpp path into build/Foo.o
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Full path to the final executable
EXECUTABLE = $(BUILD_DIR)/$(TARGET)

# Phony targets are not files — they always run when requested
.PHONY: all clean run

# Default target: build the executable
all: $(EXECUTABLE)

# Link step: combine all .o files into the executable
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS)

# Pattern rule: compile any src/*.cpp into build/*.o
# @mkdir -p $(BUILD_DIR) silently creates build/ if it doesn't exist yet
# $< is the source file (.cpp), $@ is the output file (.o)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove all build artifacts
clean:
	rm -f $(OBJS) $(EXECUTABLE)

# Build (if needed) then run
run: $(EXECUTABLE)
	$(EXECUTABLE)
