#include "MultipleChoiceQuestion.h"
#include <iostream>
#include <cctype>

//=====================================
// CHILD CLASS 1: MultipleChoiceQuestion
//=====================================

// Constructor - calls parent constructor, then initializes child members
MultipleChoiceQuestion::MultipleChoiceQuestion(std::string text, int pts, std::vector<std::string> opts, char correct)
    : Question(text, pts),      // Call parent constructor first
      options(opts),            // Initialize options vector
      correctAnswer(correct) {  // Initialize correctAnswer
    // Constructor body (empty - initializer list did everything)
}

// Destructor
MultipleChoiceQuestion::~MultipleChoiceQuestion() {
    // No manual cleanup needed
    // vector<string> automatically cleans itself up
}

// Display the question and options
void MultipleChoiceQuestion::display() {
    std::cout << "\n" << questionText << " (" << points << " points)" << std::endl;

    // Display each option with its letter
    for (size_t i = 0; i < options.size(); i++) {
        char letter = 'A' + i;  // 'A' + 0 = 'A', 'A' + 1 = 'B', etc.
        std::cout << " " << letter << ". " << options[i] << std::endl;
    }
    std::cout << "Your answer: ";
}

// Check if the user's answer is correct
bool MultipleChoiceQuestion::checkAnswer(std::string answer) {
    // Convert answer to uppercase for case-insensitive comparison
    if (answer.length() != 1) return false;  // Must be single character

    char userAnswer = toupper(answer[0]);  // Convert to uppercase
    return userAnswer == correctAnswer;    // Compare with correct answer
}
