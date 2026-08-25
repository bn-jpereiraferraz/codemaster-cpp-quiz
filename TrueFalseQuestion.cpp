#include "TrueFalseQuestion.h"
#include <iostream>
#include <cctype>

//================================
// CHILD CLASS 2: TrueFalseQuestion
//================================

// Constructor - calls parent constructor, then initializes child members
TrueFalseQuestion::TrueFalseQuestion(std::string text, int pts, bool correct)
    : Question(text, pts),      // Call parent constructor
      correctAnswer(correct) {  // Initialize correct answer
    // Constructor body (empty)
}

// Destructor
TrueFalseQuestion::~TrueFalseQuestion() {
    // No manual cleanup needed
}

// Display the question
void TrueFalseQuestion::display() {
    std::cout << "\n" << questionText << " (" << points << " points)" << std::endl;
    std::cout << "True or False?" << std::endl;
    std::cout << "Your answer (T/F): ";
}

// Check if the user's answer is correct
bool TrueFalseQuestion::checkAnswer(std::string answer) {
    if (answer.empty()) return false;  // Empty answer is wrong

    char userAnswer = toupper(answer[0]);  // Get first char, uppercase

    // Convert 'T' or 'F' to bool and compare
    if (userAnswer == 'T') {
        return correctAnswer == true;
    } else if (userAnswer == 'F') {
        return correctAnswer == false;
    }

    return false;  // Invalid input (not T or F)
}
