#ifndef GAMECONFIGURATION_H
#define GAMECONFIGURATION_H

#include "core/Gamemode.h"
#include "core/QuestionBank.h"
#include <string>

class GameConfiguration {
private:
    Gamemode gameMode;
    Difficulty difficulty;
    int questionCount;
    bool timerEnabled;
    int timerSeconds;
    bool lifelinesEnabled;
    std::string selectedCategory;

public:
    GameConfiguration();

    // Factory method for mode presets
    static GameConfiguration for_mode(Gamemode mode);

    // Setters
    void set_game_mode(Gamemode mode);
    void set_difficulty(Difficulty diff);
    void set_question_count(int count);
    void set_category(const std::string& category);
    void enable_timer(int seconds);
    void disable_timer();
    void enable_lifelines();
    void disable_lifelines();

    // Getters
    Gamemode get_game_mode() const;
    Difficulty get_difficulty() const;
    int get_question_count() const;
    std::string get_category() const;
    bool is_timer_enabled() const;
    int get_timer_seconds() const;
    bool are_lifelines_enabled() const;

    // Validation
    bool is_valid() const;
};

#endif
