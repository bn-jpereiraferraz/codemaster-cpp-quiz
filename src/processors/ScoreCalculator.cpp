#include "processors/ScoreCalculator.h"

int ScoreCalculator::calculate_points(const std::string& difficulty, int timeRemaining){
    int basePoints = 0;

    if (difficulty == "Easy") basePoints = 10;
    else if (difficulty == "Medium") basePoints = 20;
    else if (difficulty == "Hard") basePoints = 30;

    int timeBonus = calculate_time_bonus(timeRemaining, 60);

    return basePoints + timeBonus;
}

int ScoreCalculator::calculate_streak_bonus(int streak){
    if (streak >= 10) return 50;
    if (streak >= 5) return 25;
    if (streak >= 3) return 10;
    return 0;
}

int ScoreCalculator::calculate_time_bonus(int timeRemaining, int maxTime){
    if (maxTime == 0) return 0;
    if (timeRemaining <= 0) return 0;

    double percentage = (double)timeRemaining / maxTime;

    if (percentage > 0.75) return 10;
    if (percentage > 0.50) return 5;
    if (percentage > 0.25) return 2;

    return 0;
}

int ScoreCalculator::calculate_total_score(int baseScore, int streakBonus, int timeBonus){
    return baseScore + streakBonus + timeBonus;
}


