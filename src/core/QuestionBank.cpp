#include "core/QuestionBank.h"
#include "models/MultipleChoiceQuestion.h"
#include "models/TrueFalseQuestion.h"
#include "processors/QuestionProcessor.h"
#include "utils/QuestionFile.h"
#include "core/Constants.h"
#include <algorithm>

namespace DifficultyUtils {
    std::string to_string(Difficulty diff) {
        switch (diff) {
            case Difficulty::Easy:   return GameConstants::DIFF_EASY;
            case Difficulty::Medium: return GameConstants::DIFF_MEDIUM;
            case Difficulty::Hard:   return GameConstants::DIFF_HARD;
            case Difficulty::Mixed:  return GameConstants::DIFF_MIXED;
            default: return GameConstants::DIFF_MIXED;
        }
    }

    int get_points(Difficulty diff) {
        switch (diff) {
            case Difficulty::Easy:   return GameConstants::EASY_POINTS;
            case Difficulty::Medium: return GameConstants::MEDIUM_POINTS;
            case Difficulty::Hard:   return GameConstants::HARD_POINTS;
            case Difficulty::Mixed:  return 0;
            default: return 0;
        }
    }
}

QuestionBank::QuestionBank() {
}

void QuestionBank::add_question(std::unique_ptr<Question> q) {
    if (q) {
        allQuestions.push_back(std::move(q));
    }
}

void QuestionBank::load_default_questions() {
    add_question(std::make_unique<MultipleChoiceQuestion>(
        "What does OOP stand for?", 10,
        std::vector<std::string>{"Object-Oriented Programming", "Only One Person",
                                 "Out Of Pizza", "Optimize Our Programs"},
        'A'));

    add_question(std::make_unique<MultipleChoiceQuestion>(
        "Which keyword is used for inheritance in C++?", 10,
        std::vector<std::string>{"extends", "inherits", "public", "derive"},
        'C'));

    add_question(std::make_unique<TrueFalseQuestion>(
        "Pure virtual methods are declared with = 0.", 10, true));

    add_question(std::make_unique<TrueFalseQuestion>(
        "You can create objects of abstract classes.", 10, false));
}

bool QuestionBank::load_from_file(const std::string& filename) {
    auto loaded = QuestionFile::load_questions(filename);

    if (loaded.empty()) {
        return false;
    }

    for (auto& q : loaded) {
        add_question(std::move(q));
    }

    return true;
}

void QuestionBank::filter_by_difficulty(Difficulty diff) {
    std::string diffStr = DifficultyUtils::to_string(diff);

    // Clear previous filter
    filteredQuestions.clear();

    // Build new filter from allQuestions
    std::vector<Question*> rawPointers;
    for (const auto& q : allQuestions) {
        rawPointers.push_back(q.get());
    }

    filteredQuestions = QuestionProcessor::filter_by_difficulty(rawPointers, diffStr);
}

void QuestionBank::filter_by_category(const std::string& category) {
    if (category == GameConstants::CATEGORY_ALL) {
        return;
    }
    filteredQuestions = QuestionProcessor::filter_by_category(filteredQuestions, category);
}

void QuestionBank::shuffle_questions() {
    QuestionProcessor::shuffle_questions(filteredQuestions);
}

void QuestionBank::limit_to_count(size_t maxCount) {
    if (filteredQuestions.size() > maxCount) {
        filteredQuestions.resize(maxCount);
    }
}

const std::vector<Question*>& QuestionBank::get_filtered_questions() const {
    return filteredQuestions;
}

size_t QuestionBank::total_questions() const {
    return allQuestions.size();
}

size_t QuestionBank::filtered_questions_count() const {
    return filteredQuestions.size();
}

bool QuestionBank::has_questions() const {
    return !allQuestions.empty();
}

int QuestionBank::calculate_total_score() const {
    int total = 0;
    for (const auto* q : filteredQuestions) {
        total += q->get_points();
    }
    return total;
}
