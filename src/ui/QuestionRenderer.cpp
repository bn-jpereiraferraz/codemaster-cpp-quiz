#include "ui/QuestionRenderer.h"
#include "ui/ColorTheme.h"
#include "core/Constants.h"
#include <iostream>
#include <sstream>

void QuestionRenderer::display_boxed(const Question& question) {
    // Use polymorphism - each question type knows how to render itself
    question.render_boxed();
}

void QuestionRenderer::display_multiple_choice_boxed(const MultipleChoiceQuestion& mcq) {
    print_box_top();
    print_category_line(mcq.get_category());
    print_question_line(mcq.get_question_text());
    print_empty_line();
    print_box_separator();

    // Display each option
    const auto& options = mcq.get_options();
    for (size_t i = 0; i < options.size(); ++i) {
        char letter = 'A' + i;
        std::string optionLine = std::string(1, letter) + " │ " + options[i];
        print_box_line(optionLine);
    }

    print_box_bottom();
}

void QuestionRenderer::display_true_false_boxed(const TrueFalseQuestion& tfq) {
    print_box_top();
    print_category_line(tfq.get_category());
    print_question_line(tfq.get_question_text());
    print_empty_line();
    print_box_separator();

    // Display True/False options
    print_box_line("TRUE  │ The statement is correct");
    print_box_line("FALSE │ The statement is incorrect");

    print_box_bottom();
}

void QuestionRenderer::print_box_top() {
    std::cout << "╔";
    for (int i = 0; i < GameConstants::BOX_WIDTH - 2; ++i) {
        std::cout << "═";
    }
    std::cout << "╗\n";
}

void QuestionRenderer::print_box_bottom() {
    std::cout << "╚";
    for (int i = 0; i < GameConstants::BOX_WIDTH - 2; ++i) {
        std::cout << "═";
    }
    std::cout << "╝\n";
}

void QuestionRenderer::print_box_separator() {
    std::cout << "╠";
    for (int i = 0; i < GameConstants::BOX_WIDTH - 2; ++i) {
        std::cout << "═";
    }
    std::cout << "╣\n";
}

void QuestionRenderer::print_box_line(const std::string& content) {
    std::cout << "║  " << pad_to_width(content, GameConstants::BOX_CONTENT_WIDTH) << "║\n";
}

void QuestionRenderer::print_category_line(const std::string& category) {
    // Account for ANSI color codes (they don't take visual space)
    int visualLength = category.length() + 3;  // 📁 + space + text
    int padding = GameConstants::BOX_CONTENT_WIDTH - visualLength;

    std::cout << "║  📁 " << ColorTheme::CYAN << category << ColorTheme::RESET;
    for (int i = 0; i < padding; ++i) {
        std::cout << " ";
    }
    std::cout << " ║\n";
}

void QuestionRenderer::print_question_line(const std::string& question) {
    print_box_line(question);
}

void QuestionRenderer::print_empty_line() {
    std::cout << "║";
    for (int i = 0; i < GameConstants::BOX_WIDTH - 2; ++i) {
        std::cout << " ";
    }
    std::cout << "║\n";
}

std::string QuestionRenderer::pad_to_width(const std::string& text, int width) {
    std::stringstream ss;
    ss << text;

    int currentWidth = text.length();
    for (int i = currentWidth; i < width; ++i) {
        ss << " ";
    }

    return ss.str();
}
