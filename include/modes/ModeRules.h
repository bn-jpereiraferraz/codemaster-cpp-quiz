#ifndef MODERULES_H
#define MODERULES_H
#include "core/Gamemode.h"
#include <string>

class ModeRules{
public:
    //Get mode display name
    static std::string get_mode_name(Gamemode mode);

    //Get mode description
    static std::string get_mode_description(Gamemode mode);

    //Get score multiplier
    static double get_score_multiplier(Gamemode mode);

    //Check if mode allows customization
    static bool allows_customization(Gamemode mode);

    //Check if game should end
    static bool is_game_over(int lives, int questionsLeft);
};


#endif // MODERULES_H
