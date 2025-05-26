git :
	git add .
	git commit -m "Fixed bug with score display" 
	git push

# Makefile for UNO Game Project (flat directory structure)

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = uno_game

# Main target
all: $(EXECUTABLE)

# Link objects to create executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files to objects
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(EXECUTABLE) *.o

# Run the program
run: all
	gdb ./$(EXECUTABLE)

# Debug build
debug: CXXFLAGS += -g
debug: clean all

# Release build
release: CXXFLAGS += -O3
release: clean all

# Phony targets
.PHONY: all clean run debug release