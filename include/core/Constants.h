#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace GameConstants {
    // Default game settings
    constexpr int DEFAULT_LIVES = 3;
    constexpr int DEFAULT_TIMER_SECONDS = 300;
    constexpr int DEFAULT_QUESTION_COUNT = 10;

    // Timer settings
    constexpr int MIN_TIMER_SECONDS = 5;
    constexpr int MAX_TIMER_SECONDS = 600;

    // UI Box dimensions
    constexpr int BOX_WIDTH = 60;
    constexpr int BOX_CONTENT_WIDTH = 56;
    constexpr int BOX_PADDING = 2;

    // Score settings
    constexpr int EASY_POINTS = 5;
    constexpr int MEDIUM_POINTS = 10;
    constexpr int HARD_POINTS = 15;

    // Hint penalties
    constexpr double HINT_PENALTY_PERCENT = 0.1;  // 10% per hint

    // File paths
    const std::string DEFAULT_QUESTIONS_FILE = "data/questions.txt";
    const std::string FALLBACK_QUESTIONS_FILE = "../data/questions.txt";
    const std::string STATISTICS_FILE = "statistics.dat";
    const std::string DEFAULT_SAVE_FILE = "savegame.dat";

    // Game mode names
    const std::string MODE_CLASSIC = "Classic";
    const std::string MODE_QUICK_ATTACK = "Quick Attack";
    const std::string MODE_SURVIVAL = "Survival";
    const std::string MODE_MARATHON = "Marathon";
    const std::string MODE_LIGHTNING = "Lightning";
    const std::string MODE_PRACTICE = "Practice";

    // Difficulty names
    const std::string DIFF_EASY = "Easy";
    const std::string DIFF_MEDIUM = "Medium";
    const std::string DIFF_HARD = "Hard";
    const std::string DIFF_MIXED = "Mixed";

    // Category
    const std::string CATEGORY_ALL = "All";

    // Question types
    const std::string QUESTION_TYPE_MULTIPLE_CHOICE = "MultipleChoice";
    const std::string QUESTION_TYPE_TRUE_FALSE = "TrueFalse";
}

#endif
