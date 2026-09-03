#ifndef TRUEFALSEQUESTION_H
#define TRUEFALSEQUESTION_H

#include "Question.h"
#include <string>

//==================
// CHILD CLASS - True/False
//==================
class TrueFalseQuestion : public Question {
private:
    bool correctAnswer;

public:
    TrueFalseQuestion(std::string text, int pts, bool correct);
    ~TrueFalseQuestion();

    void display() override;
    void display_boxed() override;
    bool checkAnswer(std::string answer) override;
};

#endif
