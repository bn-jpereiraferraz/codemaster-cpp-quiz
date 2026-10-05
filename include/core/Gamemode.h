#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <string>
#include <map>

//==============
// GAME MODE ENUM CLASS
//==============
// Different gameplay modes with unique rules

enum class Gamemode {
    Classic,       // Normal mode configurable (current gameplay)
    QuickAttack,   // 5min timelimit, wrong answer = -15s penalty
    Survival,      // 3 lives, lose 1 per answer
    Marathon,      // All questions, track total time
    Lightning,     // 10 seconds per question (strict)
    Practice       // No pressure, see correct answers
};

// Utility functions for Gamemode
namespace GamemodeUtils {
    std::string to_string(Gamemode mode);
    std::string get_description(Gamemode mode);
}

#endif
