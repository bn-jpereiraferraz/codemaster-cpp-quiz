#ifndef MODESETUP_H
#define MODESETUP_H
#include "core/Gamemode.h"

struct ModeConfig{
    int questionCount;
    bool timerEnabled;
    int timerSeconds;
    bool lifelinesEnabled;
    int livesCount;
    bool allowSkip;

    ModeConfig()
        : questionCount(10), timerEnabled(false), timerSeconds(0), lifelinesEnabled(true), livesCount(3), allowSkip(true){}
};

class ModeSetup{
public:
    static int get_question_count(Gamemode mode);
    static bool is_timer_enabled(Gamemode mode);
    static int get_timer_seconds(Gamemode mode);
    static bool are_lifelines_enabled(Gamemode mode);
    static int get_lives_count(Gamemode mode);
    static bool is_skip_allowed(Gamemode mode);

    //Delegation Method
    static ModeConfig get_config(Gamemode mode);
};

#endif // MODESETUP_H
