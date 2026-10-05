#ifndef ACHIEVEMENTCHECKER_H
#define ACHIEVEMENTCHECKER_H
#include "models/Achievement.h"
#include "models/ResultsSummary.h"
#include <vector>

class AchievementChecker{
public:
    //Check if any achievements were earned this session
    static std::vector<Achievement> check_achievements(const ResultsSummary& results);

    //check if specific achievement types
    static bool check_perfect_score(const ResultsSummary& results);
    static bool check_speed_demon(const ResultsSummary& results);
    static bool check_streak_master(const ResultsSummary& results);
    static bool check_category_expert(const ResultsSummary& results);
};

#endif // ACHIEVEMENTCHECKER_H
