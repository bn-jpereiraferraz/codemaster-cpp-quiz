#ifndef LIVESTATSDISPLAY_H
#define LIVESTATSDISPLAY_H
#include "models/LiveStats.h"

class LiveStatsDisplay{
public:
    //Display compact stats during quiz
    static void show_live_stats(const LiveStats& stats);

    //Display progress bar
    static void show_progress_bar(int current, int total);

    //Display streak notification
    static void show_streak_notification(int streak);

    //Display score change(+points or -lives)
    static void show_score_change(int points, bool correct);
};


#endif // LIVESTATSDISPLAY_H
