#ifndef CONFIGURATIONUI_H
#define CONFIGURATIONUI_H
#include "core/Gamemode.h"
#include <string>
class ConfigurationUI{
public:
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
