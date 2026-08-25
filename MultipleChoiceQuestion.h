#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H

#include "Question.h"
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
    MultipleChoiceQuestion(std::string text, int pts, std::vector<std::string> opts, char correct);
    ~MultipleChoiceQuestion();

    void display() override;
    bool checkAnswer(std::string answer) override;

    // Getters for 50/50 lifeline
    std::vector<std::string> get_options() const { return options; }
    char get_correct_answer() const { return correctAnswer; }
};

#endif
