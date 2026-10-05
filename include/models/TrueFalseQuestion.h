#ifndef TRUEFALSEQUESTION_H
#define TRUEFALSEQUESTION_H

#include "models/Question.h"
#include "core/Constants.h"
#include <string>

//==================
// CHILD CLASS - True/False
//==================
class TrueFalseQuestion : public Question {
private:
    bool correctAnswer;

public:
    TrueFalseQuestion(const std::string& text, int pts, bool correct);
    TrueFalseQuestion(const std::string& text, int pts, bool correct, const std::string& cat);
    TrueFalseQuestion(const std::string& text, int pts, bool correct, const std::string& cat,
                     const std::string& h1, const std::string& h2, const std::string& h3);
    TrueFalseQuestion(const std::string& cat, const std::string& diff, const std::string& text,
                     const std::string& ans, int pts,
                     const std::string& h1, const std::string& h2, const std::string& h3);
    ~TrueFalseQuestion() override = default;

    // Virtual method implementations
    bool check_answer(const std::string& answer) const override;
    bool is_valid_input(const std::string& input) const override;
    std::string get_input_prompt() const override;
    std::string get_type() const override { return GameConstants::QUESTION_TYPE_TRUE_FALSE; }
    void render_boxed() const override;

    // Getter
    bool get_correct_answer() const { return correctAnswer; }
};

#endif
