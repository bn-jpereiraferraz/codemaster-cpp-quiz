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
    std::string hint1;
    std::string hint2;
    std::string hint3;

public:
    Question(std::string text, int pts);
    Question(std::string text, int pts, std::string cat);
    Question(std::string text, int pts, std::string cat, std::string h1, std::string h2, std::string h3);
    virtual ~Question();  // Virtual for proper inheritance cleanup

    // Pure virtual - children must implement
    virtual void display() = 0;
    virtual void display_boxed() = 0;
    virtual bool checkAnswer(std::string answer) = 0;

    int get_points();
    std::string get_category();
    std::string get_hint(int level);  // Get hint by level (1, 2, or 3)
};

#endif
