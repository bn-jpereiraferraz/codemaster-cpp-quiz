#include "TrueFalseQuestion.h"
#include "ColorTheme.h"
#include <iostream>
#include <cctype>

//================================
// CHILD CLASS 2: TrueFalseQuestion
//================================

// Constructor - calls parent constructor, then initializes child members
TrueFalseQuestion::TrueFalseQuestion(std::string text, int pts, bool correct)
    : Question(text, pts, "General"),      // Call parent constructor
      correctAnswer(correct) {  // Initialize correct answer
    // Constructor body (empty)
}

TrueFalseQuestion::TrueFalseQuestion(std::string text, int pts, bool correct, std::string cat)
    : Question(text, pts, cat), correctAnswer(correct){

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

//Display True/False in new formated box
void TrueFalseQuestion::display_boxed(){
    //Top
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";

    //Question text
    std::cout << "║  📁 " << ColorTheme::CYAN << category << ColorTheme::RESET;
    int catLen = category.length();
    int catPadding = 52 - catLen;
    for (int i = 0; i < catPadding; i++){
        std::cout << " ";
    }
    std::cout << " ║\n";

    std::cout << "║  " << questionText;

    //Padding
    int textLen = questionText.length();
    int padding = 56 - textLen;
    for (int i = 0; i < padding; i++){
        std::cout << " ";
    }
    std::cout << "║\n";
    std::cout << "║                                                          ║\n";

    //Separator
    std::cout << "╠══════════════════════════════════════════════════════════╣\n";

    //Display True
    std::cout << "║  TRUE  │ The statement is correct                        ║\n";

    //Display False
    std::cout << "║  FALSE │ The statement is incorrect                      ║\n";

    //Bottom
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
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
