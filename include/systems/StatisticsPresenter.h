#ifndef STATISTICSPRESENTER_H
#define STATISTICSPRESENTER_H

#include "systems/StatisticsData.h"
#include "core/Gamemode.h"

//==================
// STATISTICS PRESENTER
//==================
// Handles display/formatting logic
class StatisticsPresenter {
public:
    static void display_career_stats(const StatisticsData& data);
    static void display_mode_stats(const StatisticsData& data, Gamemode mode);
    static void display_category_stats(const StatisticsData& data);
    static void display_high_scores(const StatisticsData& data, Gamemode mode);
};

#endif
