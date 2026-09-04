#include "Question.h"

//====================================
// BASE CLASS: Question Implementation
//====================================

// Constructor - Initializes questionText and points
Question::Question(std::string text, int pts)
    : questionText(text), points(pts), category("General") {
}

Question::Question(std::string text, int pts, std::string cat)
    : questionText(text), points(pts), category(cat){

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

std::string Question::get_category(){
    return category;
}
