#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include "models/Question.h"
#include <vector>
#include <string>
#include <memory>

enum class Difficulty {
    Easy,
    Medium,
    Hard,
    Mixed
};

// Utility functions for Difficulty
namespace DifficultyUtils {
    std::string to_string(Difficulty diff);
    int get_points(Difficulty diff);
}

class QuestionBank {
private:
    std::vector<std::unique_ptr<Question>> allQuestions;
    std::vector<Question*> filteredQuestions;  // Non-owning pointers

public:
    QuestionBank();
    ~QuestionBank() = default;  // unique_ptr handles cleanup

    // Loading
    void add_question(std::unique_ptr<Question> q);
    bool load_from_file(const std::string& filename);
    void load_default_questions();

    // Filtering & Preparation
    void filter_by_difficulty(Difficulty diff);
    void filter_by_category(const std::string& category);
    void shuffle_questions();
    void limit_to_count(size_t maxCount);

    // Access
    const std::vector<Question*>& get_filtered_questions() const;
    size_t total_questions() const;
    size_t filtered_questions_count() const;
    bool has_questions() const;

    // Score calculation
    int calculate_total_score() const;
};

#endif
