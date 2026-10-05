#include "core/Gamemode.h"
#include <stdexcept>

namespace GamemodeUtils {
    std::string to_string(Gamemode mode) {
        switch (mode) {
            case Gamemode::Classic:     return "Classic";
            case Gamemode::QuickAttack: return "Quick Attack";
            case Gamemode::Survival:    return "Survival";
            case Gamemode::Marathon:    return "Marathon";
            case Gamemode::Lightning:   return "Lightning";
            case Gamemode::Practice:    return "Practice";
            default:
                throw std::invalid_argument("Unknown Gamemode");
        }
    }

    std::string get_description(Gamemode mode) {
        switch (mode) {
            case Gamemode::Classic:
                return "Normal mode - fully configurable";
            case Gamemode::QuickAttack:
                return "5min time limit, -15s penalty per wrong answer";
            case Gamemode::Survival:
                return "3 lives, lose 1 per wrong answer";
            case Gamemode::Marathon:
                return "All questions, track total completion time";
            case Gamemode::Lightning:
                return "10 seconds per question (strict timer)";
            case Gamemode::Practice:
                return "No pressure - see correct answers";
            default:
                return "Unknown mode";
        }
    }
}
