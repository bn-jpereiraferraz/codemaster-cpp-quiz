#include "models/Question.h"

//====================================
// BASE CLASS: Question Implementation
//====================================

Question::Question(const std::string& text, int pts)
    : questionText(text), points(pts), category("General"),
      difficulty("Easy"), hint1(""), hint2(""), hint3("") {
}

Question::Question(const std::string& text, int pts, const std::string& cat)
    : questionText(text), points(pts), category(cat),
      difficulty("Easy"), hint1(""), hint2(""), hint3("") {
}

Question::Question(const std::string& text, int pts, const std::string& cat,
                   const std::string& h1, const std::string& h2, const std::string& h3)
    : questionText(text), points(pts), category(cat),
      difficulty("Easy"), hint1(h1), hint2(h2), hint3(h3) {
}

Question::Question(const std::string& cat, const std::string& diff,
                   const std::string& text, int pts,
                   const std::string& h1, const std::string& h2, const std::string& h3)
    : questionText(text), points(pts), category(cat),
      difficulty(diff), hint1(h1), hint2(h2), hint3(h3) {
}

Question::~Question() {
}

int Question::get_points() const {
    return points;
}

std::string Question::get_category() const {
    return category;
}

std::string Question::get_difficulty() const {
    return difficulty;
}

std::string Question::get_question_text() const {
    return questionText;
}

std::string Question::get_hint(int level) const {
    if (level == 1) return hint1.empty() ? "No hint available" : hint1;
    else if (level == 2) return hint2.empty() ? "No hint available" : hint2;
    else if (level == 3) return hint3.empty() ? "No hint available" : hint3;
    else return "No more hints available!";
}
