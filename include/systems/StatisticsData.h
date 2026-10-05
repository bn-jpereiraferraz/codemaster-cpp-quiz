#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H

#include <map>
#include <string>
#include <vector>

//==================
// STATISTICS DATA
//==================
// Pure data storage - no business logic
struct ScoreEntry {
    int score;
    int correctCount;
    int totalQuestions;
    std::string date;
};

class StatisticsData {
public:
    // Career stats
    int totalGamesPlayed;
    int totalQuestionsAnswered;
    int totalCorrectAnswers;
    int totalPointsEarned;
    int longestStreakEver;

    // Stats per Mode (indexed by Gamemode enum)
    int gamesPlayedPerMode[6];
    int correctPerMode[6];
    int totalPerMode[6];
    int highScorePerMode[6];

    // Stats per Category
    std::map<std::string, int> categoryCorrect;
    std::map<std::string, int> categoryTotal;

    // High Scores (per mode)
    std::vector<ScoreEntry> highScores[6];

    StatisticsData();

    // Simple calculations
    double calculate_overall_accuracy() const;
    double calculate_mode_accuracy(int modeIndex) const;
    double calculate_category_accuracy(const std::string& category) const;
};

#endif
