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
    std::string difficulty;
    std::string hint1;
    std::string hint2;
    std::string hint3;

public:
    Question(const std::string& text, int pts);
    Question(const std::string& text, int pts, const std::string& cat);
    Question(const std::string& text, int pts, const std::string& cat,
             const std::string& h1, const std::string& h2, const std::string& h3);
    Question(const std::string& cat, const std::string& diff, const std::string& text,
             int pts, const std::string& h1, const std::string& h2, const std::string& h3);
    virtual ~Question();

    // Pure virtual - must be implemented by derived classes
    virtual bool check_answer(const std::string& answer) const = 0;
    virtual bool is_valid_input(const std::string& input) const = 0;
    virtual std::string get_input_prompt() const = 0;
    virtual std::string get_type() const = 0;
    virtual void render_boxed() const = 0;

    // Accessors
    int get_points() const;
    std::string get_category() const;
    std::string get_difficulty() const;
    std::string get_hint(int level) const;
    std::string get_question_text() const;
};

#endif
