#ifndef QUESTIONRENDERER_H
#define QUESTIONRENDERER_H

#include "models/Question.h"
#include "models/MultipleChoiceQuestion.h"
#include "models/TrueFalseQuestion.h"
#include <string>

//==================
// QUESTION RENDERER
//==================
// Handles all question display logic (separation of concerns)
class QuestionRenderer {
public:
    // Display question in boxed format (main display method)
    static void display_boxed(const Question& question);

    // Display specific question types
    static void display_multiple_choice_boxed(const MultipleChoiceQuestion& mcq);
    static void display_true_false_boxed(const TrueFalseQuestion& tfq);

private:
    // Helper methods for box rendering
    static void print_box_top();
    static void print_box_bottom();
    static void print_box_separator();
    static void print_box_line(const std::string& content);
    static void print_category_line(const std::string& category);
    static void print_question_line(const std::string& question);
    static void print_empty_line();
    static std::string pad_to_width(const std::string& text, int width);
};

#endif
