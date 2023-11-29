# Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Source files and executable
SRC = main.cpp city.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = myprogram

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
    rm -f $(OBJ) $(EXEC)