#ifndef GAMEMODE_H
#define GAMEMODE_H

//==============
//GAME MODE ENUM
//==============
//Different gameplay modes with unique rules

enum Gamemode{
    CLASSIC,        // Normal mode configurable (current gameplay)
    QUICK_ATTACK,   // 5min timelimit, wrong answer = -15s penalty
    SURVIVAL,       // 3 lives, lose 1 per answer
    MARATHON,       // All 300 questions, track total time
    LIGHTNING,      // 10 seconds per questions (strict)
    PRACTICE        // No pressure, see correct answers
};

#endif
