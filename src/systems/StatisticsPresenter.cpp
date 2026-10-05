#include "systems/StatisticsPresenter.h"
#include "ui/ColorTheme.h"
#include <iostream>
#include <iomanip>

void StatisticsPresenter::display_career_stats(const StatisticsData& data) {
    std::cout << "\n" << ColorTheme::CYAN
    << "═══════════════════════════════════════════════" << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::YELLOW << "           📊 CAREER STATISTICS 📊"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════" << ColorTheme::RESET << "\n\n";

    std::cout << ColorTheme::GREEN << "🎮 Total Games Played: " << ColorTheme::RESET
              << data.totalGamesPlayed << "\n";

    std::cout << ColorTheme::GREEN << "❓ Total Questions Answered: " << ColorTheme::RESET
              << data.totalQuestionsAnswered << "\n";

    std::cout << ColorTheme::GREEN << "✅ Total Correct Answers: " << ColorTheme::RESET
            << data.totalCorrectAnswers << "\n";

    if (data.totalCorrectAnswers > 0) {
        double accuracy = data.calculate_overall_accuracy();
        std::cout << ColorTheme::GREEN << "🎯 Overall Accuracy: " << ColorTheme::RESET
                  << std::fixed << std::setprecision(1) << accuracy << "%\n";
    }

    std::cout << ColorTheme::GREEN << "⭐ Total Points earned: " << ColorTheme::RESET
              << data.totalPointsEarned << "\n";

    std::cout << ColorTheme::GREEN << "🔥 Longest Streak Ever: " << ColorTheme::RESET
              << data.longestStreakEver << "\n";

    std::cout << ColorTheme::GREEN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

void StatisticsPresenter::display_mode_stats(const StatisticsData& data, Gamemode mode) {
    int modeIndex = static_cast<int>(mode);

    std::cout << "\n" << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::YELLOW << "      📊 " << GamemodeUtils::to_string(mode) << " MODE STATS 📊"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n\n";

    std::cout << ColorTheme::GREEN << "🎮 Games Played: " << ColorTheme::RESET
              << data.gamesPlayedPerMode[modeIndex] << "\n";

    std::cout << ColorTheme::GREEN << "❓ Questions Answered: " << ColorTheme::RESET
              << data.totalPerMode[modeIndex] << "\n";

    std::cout << ColorTheme::GREEN << "✅ Correct Answers: " << ColorTheme::RESET
              << data.correctPerMode[modeIndex] << "\n";

    if (data.totalPerMode[modeIndex] > 0) {
        double accuracy = data.calculate_mode_accuracy(modeIndex);
        std::cout << ColorTheme::GREEN << "🎯 Accuracy: " << ColorTheme::RESET
                  << std::fixed << std::setprecision(1) << accuracy << "%\n";
    }

    std::cout << ColorTheme::GREEN << "🏆 High Score: " << ColorTheme::RESET
              << data.highScorePerMode[modeIndex] << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

void StatisticsPresenter::display_category_stats(const StatisticsData& data) {
    std::cout << "\n" << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::YELLOW << "      📁 CATEGORY PERFORMANCE 📁" << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n\n";

    if (data.categoryTotal.empty()) {
        std::cout << ColorTheme::DIM << "No category data. Play some games!\n" << ColorTheme::RESET;
        std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
                  << ColorTheme::RESET << "\n";
        return;
    }

    for (const auto& pair : data.categoryTotal) {
        std::string category = pair.first;
        int total = pair.second;
        int correct = 0;

        auto it = data.categoryCorrect.find(category);
        if (it != data.categoryCorrect.end()) {
            correct = it->second;
        }

        double accuracy = data.calculate_category_accuracy(category);

        std::cout << ColorTheme::GREEN << "📁 " << category << ": " << ColorTheme::RESET;
        std::cout << correct << "/" << total << " ";
        std::cout << "(" << std::fixed << std::setprecision(1) << accuracy << "%)\n";
    }

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

void StatisticsPresenter::display_high_scores(const StatisticsData& data, Gamemode mode) {
    int modeIndex = static_cast<int>(mode);

    std::cout << "\n" << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::YELLOW << "   🏆 TOP 5 HIGH SCORES - " << GamemodeUtils::to_string(mode) << " 🏆"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n\n";

    if (data.highScores[modeIndex].empty()) {
        std::cout << ColorTheme::DIM << "No High Scores yet. Make some Quiz runs in "
                  << GamemodeUtils::to_string(mode) << " mode!\n" << ColorTheme::RESET;

        std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
                  << ColorTheme::RESET << "\n";
        return;
    }

    for(size_t i = 0; i < data.highScores[modeIndex].size(); i++) {
        const ScoreEntry& entry = data.highScores[modeIndex][i];

        std::cout << ColorTheme::YELLOW;
        if (i == 0) std::cout << "🥇 1.";
        else if (i == 1) std::cout << "🥈 2.";
        else if (i == 2) std::cout << "🥉 3.";
        else std::cout << (i + 1) << ". ";
        std::cout << ColorTheme::RESET;

        std::cout << ColorTheme::GREEN << entry.score << " pts" << ColorTheme::RESET << " | ";
        std::cout << entry.correctCount << "/" << entry.totalQuestions << " | ";
        std::cout << ColorTheme::DIM << entry.date << ColorTheme::RESET << "\n";
    }

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}
