#include "modes/ModeRules.h"

std::string ModeRules::get_mode_name(Gamemode mode){
    switch(mode){
        case Gamemode::Classic:
            return "Classic";
        case Gamemode::QuickAttack:
            return "Quick Attack";
        case Gamemode::Survival:
            return "Survival";
        case Gamemode::Marathon:
            return "Marathon";
        case Gamemode::Lightning:
            return "Lightning";
        case Gamemode::Practice:
            return "Practice";
        default:
            return "Unknown";
    }
}

std::string ModeRules::get_mode_description(Gamemode mode){
    switch(mode){
        case Gamemode::Classic:
            return "Classic quiz mode - fully customizable settings";
        case Gamemode::QuickAttack:
            return "Speed challenge - 30s per question, no lifelines";
        case Gamemode::Survival:
            return "Increasing difficulty - 3 lives, survive as long as you can";
        case Gamemode::Marathon:
            return "Endurance test - 50 questions, 5 lives";
        case Gamemode::Lightning:
            return "Rapid fire - 15s per question, extreme speed";
        case Gamemode::Practice:
            return "Practice mode - unlimited lives, no pressure";
        default:
            return "Unknown mode";
    }
}

double ModeRules::get_score_multiplier(Gamemode mode){
    switch(mode){
        case Gamemode::QuickAttack: return 1.5;
        case Gamemode::Lightning: return 2.0;
        case Gamemode::Survival: return 1.3;
        case Gamemode::Marathon: return 1.2;
        case Gamemode::Practice: return 0.5;
        default: return 1.0;
    }
}

bool ModeRules::allows_customization(Gamemode mode){
    return mode == Gamemode::Classic;
}

bool ModeRules::is_game_over(int lives, int questionsLeft){
    if (lives <= 0) return true;
    if (questionsLeft <= 0) return true;
    return false;
}
