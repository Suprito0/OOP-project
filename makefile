# Makefile for UNO Game Project 

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
SOURCES = ActionCard.cpp AIPlayer.cpp Card.cpp Deck.cpp Game.cpp GameMode.cpp HumanPlayer.cpp main.cpp NumberCard.cpp Player.cpp SpecialActionCard.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = unoGame

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
	./$(EXECUTABLE)

# Debug build
debug: CXXFLAGS += -g
debug: clean all

# Release build
release: CXXFLAGS += -O3
release: clean all

# Phony targets
.PHONY: all clean run debug release