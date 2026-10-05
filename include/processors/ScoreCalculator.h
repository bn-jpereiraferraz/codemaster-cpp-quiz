#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H
#include <string>

class ScoreCalculator {
public:
    //Calculate points for correct answer
    static int calculate_points(const std::string& difficulty, int timeRemaining);

    //Calculate bonus for streak
    static int calculate_streak_bonus(int streak);

    //Calculate time bonus
    static int calculate_time_bonus(int timeRemaining, int maxTime);

    //Calculate final score with all bonuses
    static int calculate_total_score(int baseScore, int streakBonus, int timeBonus);
};

#endif // SCORECALCULATOR_H
