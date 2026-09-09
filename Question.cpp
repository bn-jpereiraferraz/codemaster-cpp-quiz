#include "Question.h"

//====================================
// BASE CLASS: Question Implementation
//====================================

// Constructor - Initializes questionText and points (no hints)
Question::Question(std::string text, int pts)
    : questionText(text), points(pts), category("General"), hint1(""), hint2(""), hint3("") {
}

// Constructor with category (no hints)
Question::Question(std::string text, int pts, std::string cat)
    : questionText(text), points(pts), category(cat), hint1(""), hint2(""), hint3("") {
}

// Constructor with category and hints
Question::Question(std::string text, int pts, std::string cat, std::string h1, std::string h2, std::string h3)
    : questionText(text), points(pts), category(cat), hint1(h1), hint2(h2), hint3(h3) {
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

// Get hint by level (1, 2, or 3)
std::string Question::get_hint(int level) {
    if (level == 1) return hint1;
    else if (level == 2) return hint2;
    else if (level == 3) return hint3;
    else return "No more hints available!";
}
