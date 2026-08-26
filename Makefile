# Makefile for CodeMaster C++ Quiz

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = quiz

SOURCES = main.cpp \
          ColorTheme.cpp \
          Question.cpp \
          MultipleChoiceQuestion.cpp \
          TrueFalseQuestion.cpp \
          Timer.cpp \
          Lifelines.cpp \
          GlobalTimer.cpp \
          Lives.cpp \
          QuizGame.cpp

HEADERS = ColorTheme.h \
          Question.h \
          MultipleChoiceQuestion.h \
          TrueFalseQuestion.h \
          Timer.h \
          Lifelines.h \
          GlobalTimer.h \
          Lives.h \
          QuizGame.h

OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the quiz
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
