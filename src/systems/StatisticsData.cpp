#include "systems/StatisticsData.h"

StatisticsData::StatisticsData()
    : totalGamesPlayed(0),
      totalQuestionsAnswered(0),
      totalCorrectAnswers(0),
      totalPointsEarned(0),
      longestStreakEver(0) {

    for (int i = 0; i < 6; i++) {
        gamesPlayedPerMode[i] = 0;
        correctPerMode[i] = 0;
        totalPerMode[i] = 0;
        highScorePerMode[i] = 0;
    }
}

double StatisticsData::calculate_overall_accuracy() const {
    if (totalQuestionsAnswered == 0) return 0.0;
    return (static_cast<double>(totalCorrectAnswers) / totalQuestionsAnswered) * 100.0;
}

double StatisticsData::calculate_mode_accuracy(int modeIndex) const {
    if (modeIndex < 0 || modeIndex >= 6) return 0.0;
    if (totalPerMode[modeIndex] == 0) return 0.0;
    return (static_cast<double>(correctPerMode[modeIndex]) / totalPerMode[modeIndex]) * 100.0;
}

double StatisticsData::calculate_category_accuracy(const std::string& category) const {
    auto totalIt = categoryTotal.find(category);
    auto correctIt = categoryCorrect.find(category);

    if (totalIt == categoryTotal.end() || totalIt->second == 0) return 0.0;
    if (correctIt == categoryCorrect.end()) return 0.0;

    return (static_cast<double>(correctIt->second) / totalIt->second) * 100.0;
}
