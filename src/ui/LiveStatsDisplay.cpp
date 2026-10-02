#include "ui/LiveStatsDisplay.h"
#include "ui/ColorTheme.h"
#include <iostream> 
#include <iomanip>

void LiveStatsDisplay::show_live_stats(const LiveStats& stats){
    std::cout << ColorTheme::DIM;
    std::cout << "  Q: " << stats.currentQuestion << "/" << stats.totalQuestions;
    std::cout << " | ✓ " << stats.correctAnswers;
    std::cout << " | ✗ " << stats.wrongAnswers;
    std::cout << " | Score: " << stats.score;

    if (stats.currentStreak > 0){
        std::cout << " | Streak: " << stats.currentStreak;
    }

    if (stats.remainingLives > 0) {
        std::cout << " | Lives: " << stats.remainingLives;
    }

    std::cout << ColorTheme::RESET << "\n";
}

void LiveStatsDisplay::show_progress_bar(int current, int total){
    if (total == 0) return;

    double percentage = (current * 100.0) / total;
    int barWidth = 30;
    int filled = (int)((percentage / 100.0) * barWidth);

    std::cout << ColorTheme::CYAN << "  Progress: [";

    for (int i = 0; i < barWidth; i++){
        if (i < filled) std::cout << "█";
        else std::cout << "░";
    }

    std::cout << "] " << std::fixed << std::setprecision(1) << percentage << "%\n" << ColorTheme::RESET;
}

void LiveStatsDisplay::show_streak_notification(int streak){
    if (streak >= 5){
        std::cout << ColorTheme::YELLOW << "  🔥 " << streak << " in a row! " << ColorTheme::RESET << "\n";
    }
}

void LiveStatsDisplay::show_score_change(int points, bool correct){
    if (correct){
        std::cout << ColorTheme::GREEN << "  +" << points << " points" << ColorTheme::RESET << "\n";
    }else{
        std::cout << ColorTheme::RED << "  -1 life" << ColorTheme::RESET << "\n";
    }
}

