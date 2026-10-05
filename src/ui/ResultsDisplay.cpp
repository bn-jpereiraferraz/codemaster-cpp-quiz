#include "ui/ResultsDisplay.h"
#include "ui/ColorTheme.h"
#include <iostream>
#include <iomanip>

void ResultsDisplay::show_results(const ResultsSummary& results, Gamemode /* mode */){
    // mode parameter reserved for future mode-specific display customization
    std::cout << "\n\n";
    ColorTheme::print_separator();
    ColorTheme::print_separator();

    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n    🏆 QUIZ RESULTS 🏆\n\n" << ColorTheme::RESET;

    show_grade(results.grade, results.get_score_percentage());
    show_performance_stats(results);

    if (results.newHighScore){
        std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
        std::cout << "\n    ⭐ NEW HIGH SCORE! ⭐\n" << ColorTheme::RESET;
    }

    ColorTheme::print_separator();
}

void ResultsDisplay::show_grade(const std::string& grade, double percentage){
    std::string color;

    if (percentage >= 90) color = ColorTheme::GREEN;
    else if (percentage >= 80) color = ColorTheme::CYAN;
    else if (percentage >= 70) color = ColorTheme::YELLOW;
    else if (percentage >= 60) color = ColorTheme::MAGENTA;
    else color = ColorTheme::RED;

    std::cout << color << ColorTheme::BOLD;
    std::cout << "    Grade: " << grade << " (" << std::fixed << std::setprecision(1) << percentage << "%)\n" << ColorTheme::RESET;
}

void ResultsDisplay::show_performance_stats(const ResultsSummary& results){
    std::cout << ColorTheme::CYAN << "\n  📊 Performance:\n" << ColorTheme::RESET;
    std::cout << "    Correct: " << ColorTheme::GREEN << results.correctAnswers << ColorTheme::RESET << " / " << results.totalQuestions << "\n";
    std::cout << "    Wrong: " << ColorTheme::RED << results.wrongAnswers << ColorTheme::RESET << "\n";
    std::cout << "    Best Streak: " << results.bestStreak << "\n";

    if (results.timeSpent > 0){
        int minutes = results.timeSpent / 60;
        int seconds = results.timeSpent % 60;
        std::cout << "    Time: " << minutes << "m " << seconds << "s\n";
    }
}

void ResultsDisplay::show_achievements_earned(const ResultsSummary& results){
    if (results.perfectScore){
        std::cout << ColorTheme::YELLOW << "\n    🎖️  Perfect Score Achievement!\n" << ColorTheme::RESET;
    }
}