# ================================================
# C++ Quiz Game - New Modular Makefile
# ================================================

# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14 -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build
TARGET = $(BIN_DIR)/quiz

# Colors for output
COLOR_RESET = \033[0m
COLOR_GREEN = \033[32m
COLOR_YELLOW = \033[33m
COLOR_CYAN = \033[36m

# Source files (find all .cpp recursively in src/)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')

# Object files (mirror src structure in build/obj)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Dependency files
DEPS = $(OBJECTS:.o=.d)

# ================================================
# TARGETS
# ================================================

# Default target
all: banner $(TARGET)
	@echo "$(COLOR_GREEN)✅ Build complete!$(COLOR_RESET)"

# Banner
banner:
	@echo "$(COLOR_CYAN)"
	@echo "╔══════════════════════════════════════╗"
	@echo "║     Building C++ Quiz Game...       ║"
	@echo "╚══════════════════════════════════════╝"
	@echo "$(COLOR_RESET)"

# Link executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	@echo "$(COLOR_YELLOW)🔗 Linking executable...$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
	@echo "$(COLOR_GREEN)✅ Linked: $(TARGET)$(COLOR_RESET)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "$(COLOR_CYAN)🔨 Compiling: $<$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build artifacts
clean:
	@echo "$(COLOR_YELLOW)🧹 Cleaning build artifacts...$(COLOR_RESET)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "$(COLOR_GREEN)✅ Clean complete!$(COLOR_RESET)"

# Run the game
run: $(TARGET)
	@echo "$(COLOR_CYAN)"
	@echo "╔══════════════════════════════════════╗"
	@echo "║        Running Quiz Game...          ║"
	@echo "╚══════════════════════════════════════╝"
	@echo "$(COLOR_RESET)"
	@cd $(BIN_DIR) && ./quiz

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: clean all
	@echo "$(COLOR_GREEN)✅ Debug build complete!$(COLOR_RESET)"

# Show file structure
structure:
	@echo "$(COLOR_CYAN)📂 Project Structure:$(COLOR_RESET)"
	@tree -L 3 -I 'build|.git' || find . -type d -maxdepth 3 | grep -v build | grep -v .git | sort

# Show compilation commands
verbose: CXXFLAGS += -v
verbose: clean all

# Help
help:
	@echo "$(COLOR_CYAN)"
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make run      - Build and run the game"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make structure - Show project structure"
	@echo "  make help     - Show this help"
	@echo "$(COLOR_RESET)"

.PHONY: all clean run debug structure help banner verbose
