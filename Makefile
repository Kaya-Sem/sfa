
# Makefile

CXX = g++               # Set the C++ compiler
CXXFLAGS = -std=c++17    # Specify the C++ standard
LDFLAGS =                # Linker flags (if needed)
SRC = main.cpp watcher.cpp  # Source files
OBJ = $(SRC:.cpp=.o)     # Object files
EXEC = sfa   # Output executable

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp watcher.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)
