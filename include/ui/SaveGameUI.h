#ifndef SAVEGAMEUI_H
#define SAVEGAMEUI_H
#include <string>

class SaveGameUI{
public:
    //Display save game prompt
    static void show_save_prompt();
    
    //Display load game prompt
    static void show_load_prompt();
    
    //Display save success message
    static void show_save_success(const std::string& filename);

    //Display save error message
    static void show_save_error(const std::string& message);

    //Display load success message
    static void show_load_success();

    //Display load error message
    static void show_load_error(const std::string& message);
};
#endif // SAVEGAMEUI_H
