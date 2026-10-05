#ifndef STATISTICS_H
#define STATISTICS_H

#include "systems/StatisticsData.h"
#include "systems/StatisticsRepository.h"
#include "systems/StatisticsPresenter.h"
#include "core/Gamemode.h"
#include <string>

//==================
// STATISTICS FACADE
//==================
// Provides backward-compatible interface wrapping the new focused classes
class Statistics {
private:
    StatisticsData data;

public:
    Statistics();

    // Update Methods
    void record_game(Gamemode mode, int score, int correct, int total, int streak);
    void record_category_performance(const std::string& category, bool correct);

    // Save/Load mechanism
    bool save_to_file(const std::string& filename);
    bool load_from_file(const std::string& filename);

    // Display
    void display_career_stats();
    void display_mode_stats(Gamemode mode);
    void display_category_stats();
    void display_high_scores(Gamemode mode);
};

#endif
