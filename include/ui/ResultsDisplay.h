#ifndef RESULTSDISPLAY_H
#define RESULTSDISPLAY_H
#include "models/ResultsSummary.h"
#include "core/Gamemode.h"
#include <string>

class ResultsDisplay {
public:
    //Display final results screen
    static void show_results(const ResultsSummary& results, Gamemode mode);

    //Display grade with color
    static void show_grade(const std::string& grade, double percentage);

    //Display performance breakdown
    static void show_performance_stats(const ResultsSummary& results);

    //Display achievements earned (if any)
    static void show_achievements_earned(const ResultsSummary& results);
};


#endif // RESULTSDISPLAY_H
