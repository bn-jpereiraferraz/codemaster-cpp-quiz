#include "modes/ModeSetup.h"

int ModeSetup::get_question_count(Gamemode mode){
    switch(mode){
        case Gamemode::Classic:
            return 10;
        case Gamemode::QuickAttack:
            return 15;
        case Gamemode::Survival:
            return 20;
        case Gamemode::Marathon:
            return 50;
        case Gamemode::Lightning:
            return 25;
        case Gamemode::Practice:
            return 10;
        default:
            return 10;
    }
}

bool ModeSetup::is_timer_enabled(Gamemode mode){
    return mode == Gamemode::QuickAttack || mode == Gamemode::Lightning;
}

int ModeSetup::get_timer_seconds(Gamemode mode){
    switch(mode){
        case Gamemode::QuickAttack:
            return 30;
        case Gamemode::Lightning:
            return 15;
        default:
            return 0;
    }
}

bool ModeSetup::are_lifelines_enabled(Gamemode mode){
    return mode != Gamemode::QuickAttack && mode != Gamemode::Lightning;
}

int ModeSetup::get_lives_count(Gamemode mode){
    switch(mode){
        case Gamemode::Classic:
            return 3;
        case Gamemode::QuickAttack:
            return 1;
        case Gamemode::Survival:
            return 3;
        case Gamemode::Marathon:
            return 5;
        case Gamemode::Lightning:
            return 1;
        case Gamemode::Practice:
            return 999;
        default:
            return 3;
    }
}

bool ModeSetup::is_skip_allowed(Gamemode mode){
    return mode == Gamemode::Practice;
}

ModeConfig ModeSetup::get_config(Gamemode mode){
    ModeConfig config;
    config.questionCount = get_question_count(mode);
    config.timerEnabled = is_timer_enabled(mode);
    config.timerSeconds = get_timer_seconds(mode);
    config.lifelinesEnabled = are_lifelines_enabled(mode);
    config.livesCount = get_lives_count(mode);
    config.allowSkip = is_skip_allowed(mode);
    return config;
}
