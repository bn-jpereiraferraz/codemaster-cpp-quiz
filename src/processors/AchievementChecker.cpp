#include "processors/AchievementChecker.h"

std::vector<Achievement> AchievementChecker::check_achievements(const ResultsSummary& results){
    std::vector<Achievement> earned;

    if (check_perfect_score(results)){
        earned.push_back(Achievement("Perfect Score", "Get 100% on a quiz", "🏆"));
    }

    if (check_speed_demon(results)){
        earned.push_back(Achievement("Speed Demon", "Complete quiz in record time", "⚡ "));
    }

    if (check_streak_master(results)){
        earned.push_back(Achievement("Streak Master", "Get 10+ correct in  a row", "🔥"));
    }
    return earned;
}

bool AchievementChecker::check_perfect_score(const ResultsSummary& results){
    return results.perfectScore;
}

bool AchievementChecker::check_speed_demon(const ResultsSummary& results){
    return results.timeSpent > 0 && results.timeSpent < 300;
}

bool AchievementChecker::check_streak_master(const ResultsSummary& results){
    return results.bestStreak >= 10;
}

bool AchievementChecker::check_category_expert(const ResultsSummary& results){
    return results.get_accuracy() >= 90.0;
}


