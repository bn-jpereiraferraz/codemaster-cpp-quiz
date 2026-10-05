#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H

#include "models/Question.h"
#include "core/Constants.h"
#include <vector>
#include <string>

//==================
// CHILD CLASS - Multiple Choice (4 options)
//==================
class MultipleChoiceQuestion : public Question {
private:
    std::vector<std::string> options;  // A, B, C, D options
    char correctAnswer;                // Correct option letter

public:
    MultipleChoiceQuestion(const std::string& text, int pts,
                          const std::vector<std::string>& opts, char correct);
    MultipleChoiceQuestion(const std::string& text, int pts,
                          const std::vector<std::string>& opts, char correct,
                          const std::string& cat);
    MultipleChoiceQuestion(const std::string& text, int pts,
                          const std::vector<std::string>& opts, char correct,
                          const std::string& cat,
                          const std::string& h1, const std::string& h2, const std::string& h3);
    MultipleChoiceQuestion(const std::string& cat, const std::string& diff,
                          const std::string& text,
                          const std::vector<std::string>& opts,
                          const std::string& ans, int pts,
                          const std::string& h1, const std::string& h2, const std::string& h3);
    ~MultipleChoiceQuestion() override = default;

    // Virtual method implementations
    bool check_answer(const std::string& answer) const override;
    bool is_valid_input(const std::string& input) const override;
    std::string get_input_prompt() const override;
    std::string get_type() const override { return GameConstants::QUESTION_TYPE_MULTIPLE_CHOICE; }
    void render_boxed() const override;

    // Getters for rendering and 50/50 lifeline
    const std::vector<std::string>& get_options() const { return options; }
    char get_correct_answer() const { return correctAnswer; }
};

#endif
