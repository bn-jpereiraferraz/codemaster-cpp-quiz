#include "Question.h"

//====================================
// BASE CLASS: Question Implementation
//====================================

// Constructor - Initializes questionText and points
Question::Question(std::string text, int pts)
    : questionText(text), points(pts) {
}

// Virtual Destructor
Question::~Question() {
    // Empty but necessary for proper inheritance cleanup
    // When a child object is deleted through a base pointer
    // this ensures the chain of destructors is called properly
}

// Points getter
int Question::get_points() {
    return points;
}
