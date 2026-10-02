#ifndef ACHIEVEMENTDISPLAY_H
#define ACHIEVEMENTDISPLAY_H
#include "models/Achievement.h"
#include <vector>

class AchievementDisplay{
public: 
    //Display all achievements
    static void show_all_achievements(const std::vector<Achievement>& achievements);

    //Display only unlocked achievements
    static void show_unlocked_achievements(const std::vector<Achievement>& achievements);

    //Display achievement unlock notification
    static void show_unlock_notfication(const Achievement& achievement);

    //Display achievement progress
    static void show_achievement_progress(const std::string& name, int current, int required);

};

#endif // ACHIEVEMENTDISPLAY_H
