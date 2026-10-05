#include "models/TrueFalseQuestion.h"
#include "ui/QuestionRenderer.h"
#include <cctype>
#include <algorithm>

//================================
// CHILD CLASS 2: TrueFalseQuestion
//================================

TrueFalseQuestion::TrueFalseQuestion(const std::string& text, int pts, bool correct)
    : Question(text, pts, "General"),
      correctAnswer(correct) {
}

TrueFalseQuestion::TrueFalseQuestion(const std::string& text, int pts, bool correct,
                                    const std::string& cat)
    : Question(text, pts, cat),
      correctAnswer(correct) {
}

TrueFalseQuestion::TrueFalseQuestion(const std::string& text, int pts, bool correct,
                                    const std::string& cat,
                                    const std::string& h1, const std::string& h2,
                                    const std::string& h3)
    : Question(text, pts, cat, h1, h2, h3),
      correctAnswer(correct) {
}

TrueFalseQuestion::TrueFalseQuestion(const std::string& cat, const std::string& diff,
                                    const std::string& text, const std::string& ans,
                                    int pts, const std::string& h1,
                                    const std::string& h2, const std::string& h3)
    : Question(cat, diff, text, pts, h1, h2, h3),
      correctAnswer(ans == "True" || ans == "true" || ans == "T" || ans == "t") {
}

bool TrueFalseQuestion::check_answer(const std::string& answer) const {
    if (answer.empty()) return false;

    std::string lowerAnswer = answer;
    std::transform(lowerAnswer.begin(), lowerAnswer.end(), lowerAnswer.begin(), ::tolower);

    bool userAnswer;
    if (lowerAnswer == "true" || lowerAnswer == "t") {
        userAnswer = true;
    } else if (lowerAnswer == "false" || lowerAnswer == "f") {
        userAnswer = false;
    } else {
        return false;  // Invalid input
    }

    return userAnswer == correctAnswer;
}

bool TrueFalseQuestion::is_valid_input(const std::string& input) const {
    if (input.empty()) return false;

    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    return lowerInput == "true" || lowerInput == "false" ||
           lowerInput == "t" || lowerInput == "f";
}

std::string TrueFalseQuestion::get_input_prompt() const {
    return "Please enter T (True) or F (False)";
}

void TrueFalseQuestion::render_boxed() const {
    QuestionRenderer::display_true_false_boxed(*this);
}
