#include "models/MultipleChoiceQuestion.h"
#include "ui/QuestionRenderer.h"
#include <cctype>
#include <algorithm>

//=====================================
// CHILD CLASS 1: MultipleChoiceQuestion
//=====================================

MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& text, int pts,
                                              const std::vector<std::string>& opts, char correct)
    : Question(text, pts, "General"),
      options(opts),
      correctAnswer(std::toupper(correct)) {
}

MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& text, int pts,
                                              const std::vector<std::string>& opts,
                                              char correct, const std::string& cat)
    : Question(text, pts, cat),
      options(opts),
      correctAnswer(std::toupper(correct)) {
}

MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& text, int pts,
                                              const std::vector<std::string>& opts,
                                              char correct, const std::string& cat,
                                              const std::string& h1, const std::string& h2,
                                              const std::string& h3)
    : Question(text, pts, cat, h1, h2, h3),
      options(opts),
      correctAnswer(std::toupper(correct)) {
}

MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& cat, const std::string& diff,
                                              const std::string& text,
                                              const std::vector<std::string>& opts,
                                              const std::string& ans, int pts,
                                              const std::string& h1, const std::string& h2,
                                              const std::string& h3)
    : Question(cat, diff, text, pts, h1, h2, h3),
      options(opts),
      correctAnswer(ans.empty() ? 'A' : std::toupper(ans[0])) {
}

bool MultipleChoiceQuestion::check_answer(const std::string& answer) const {
    if (answer.empty()) return false;
    char userAnswer = std::toupper(answer[0]);
    return userAnswer == correctAnswer;
}

bool MultipleChoiceQuestion::is_valid_input(const std::string& input) const {
    if (input.length() != 1) return false;

    char inputChar = std::toupper(input[0]);
    char maxOption = 'A' + static_cast<char>(options.size()) - 1;

    return inputChar >= 'A' && inputChar <= maxOption;
}

std::string MultipleChoiceQuestion::get_input_prompt() const {
    std::string prompt = "Please enter ";
    size_t numOptions = options.size();

    for (size_t i = 0; i < numOptions; ++i) {
        if (i > 0 && i == numOptions - 1) {
            prompt += " or ";
        } else if (i > 0) {
            prompt += ", ";
        }
        prompt += char('A' + i);
    }

    return prompt;
}

void MultipleChoiceQuestion::render_boxed() const {
    QuestionRenderer::display_multiple_choice_boxed(*this);
}
