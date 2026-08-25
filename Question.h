#ifndef QUESTION_H
#define QUESTION_H

#include <string>

//==================
// BASE CLASS - Abstract Question
//==================
class Question {
protected:
    std::string questionText;
    int points;

public:
    Question(std::string text, int pts);
    virtual ~Question();  // Virtual for proper inheritance cleanup

    // Pure virtual - children must implement
    virtual void display() = 0;
    virtual bool checkAnswer(std::string answer) = 0;

    int get_points();
};

#endif
