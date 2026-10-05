#ifndef CONFIGURATIONUI_H
#define CONFIGURATIONUI_H
#include "core/Gamemode.h"
#include <string>

class ConfigurationUI{
public:
    //Display configuration header
    static void show_header();

    //Prompt and get question count
    static int prompt_question_count(Gamemode mode);

    //Prompt and get difficulty choice
    static int prompt_difficulty();

    //Prompt and get category choice
    static int prompt_category();

    //Prompt and get timer choice
    static int prompt_timer(Gamemode mode);

    //Prompt and get lifelines choice
    static int prompt_lifelines(Gamemode mode);

    //Show configuration complete message
    static void show_complete();

    //Display configuration summary
    static void show_config_summary(int questionCount, const std::string& difficulty, const std::string& category, bool timerEnabled, int timerSeconds, bool lifelinesEnabled);

    //Display mode specific configuration info
    static void show_mode_config_info(Gamemode mode);

    //Display timer options
    static void show_timer_options();

    //Display lifeline options
    static void show_lifeline_options();
};

#endif // CONFIGURATIONUI_H
