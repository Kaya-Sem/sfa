# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS =

# Directories
SRC_DIR = .
BUILD_DIR = build
TRANSDUCER_DIR = transducer
WATCHER_DIR = watcher
MEMGRAPH_DIR = memgraph

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) \
       $(wildcard $(TRANSDUCER_DIR)/*.cpp) \
       $(wildcard $(MEMGRAPH_DIR)/*.cpp) \
       $(wildcard $(WATCHER_DIR)/*.cpp)

# Object files (maintain directory structure in build folder)
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Output executable
EXEC = $(BUILD_DIR)/sfa

# Default target
all: prep $(EXEC)

# Create build directory structure
prep:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/$(TRANSDUCER_DIR)
	@mkdir -p $(BUILD_DIR)/$(WATCHER_DIR)
	@mkdir -p $(BUILD_DIR)/$(MEMGRAPH_DIR)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build directory and executable
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all prep clean
