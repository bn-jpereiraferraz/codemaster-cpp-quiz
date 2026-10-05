#include "systems/statistics.h"
#include <algorithm>
#include <ctime>

Statistics::Statistics() : data() {
}

void Statistics::record_game(Gamemode mode, int score, int correct, int total, int streak) {
    // Update career stats
    data.totalGamesPlayed++;
    data.totalQuestionsAnswered += total;
    data.totalCorrectAnswers += correct;
    data.totalPointsEarned += score;

    if (streak > data.longestStreakEver) {
        data.longestStreakEver = streak;
    }

    // Update per mode stats
    int modeIndex = static_cast<int>(mode);
    data.gamesPlayedPerMode[modeIndex]++;
    data.correctPerMode[modeIndex] += correct;
    data.totalPerMode[modeIndex] += total;

    if (score > data.highScorePerMode[modeIndex]) {
        data.highScorePerMode[modeIndex] = score;
    }

    // Add to high scores list
    ScoreEntry entry;
    entry.score = score;
    entry.correctCount = correct;
    entry.totalQuestions = total;

    // Get current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateStr[32];
    snprintf(dateStr, sizeof(dateStr), "%04d-%02d-%02d",
             1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    entry.date = dateStr;

    data.highScores[modeIndex].push_back(entry);

    // Keep only top 5 scores
    std::sort(data.highScores[modeIndex].begin(), data.highScores[modeIndex].end(),
              [](const ScoreEntry& a, const ScoreEntry& b) {
                  return a.score > b.score;
              });

    if (data.highScores[modeIndex].size() > 5) {
        data.highScores[modeIndex].resize(5);
    }
}

void Statistics::record_category_performance(const std::string& category, bool correct) {
    data.categoryTotal[category]++;

    if (correct) {
        data.categoryCorrect[category]++;
    }
}

bool Statistics::save_to_file(const std::string& filename) {
    return StatisticsRepository::save_to_file(data, filename);
}

bool Statistics::load_from_file(const std::string& filename) {
    return StatisticsRepository::load_from_file(data, filename);
}

void Statistics::display_career_stats() {
    StatisticsPresenter::display_career_stats(data);
}

void Statistics::display_mode_stats(Gamemode mode) {
    StatisticsPresenter::display_mode_stats(data, mode);
}

void Statistics::display_category_stats() {
    StatisticsPresenter::display_category_stats(data);
}

void Statistics::display_high_scores(Gamemode mode) {
    StatisticsPresenter::display_high_scores(data, mode);
}
