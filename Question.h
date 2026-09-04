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
    std::string category;

public:
    Question(std::string text, int pts);
    Question(std::string text, int pts, std::string cat);
    virtual ~Question();  // Virtual for proper inheritance cleanup

    // Pure virtual - children must implement
    virtual void display() = 0;
    virtual void display_boxed() = 0;
    virtual bool checkAnswer(std::string answer) = 0;

    int get_points();
    std::string get_category();
};

#endif
