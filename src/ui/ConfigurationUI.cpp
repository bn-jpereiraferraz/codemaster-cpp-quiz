#include "ui/ConfigurationUI.h"
#include "ui/ColorTheme.h"
#include <iostream>

void ConfigurationUI::show_config_summary(int questionCount, const std::string& difficulty, const std::string& category, bool timerEnabled, int timerSeconds, bool lifelinesEnabled){
    std::cout << "\n";
    ColorTheme::print_separator();
    std::cout << ColorTheme::GREEN << ColorTheme::BOLD;
    std::cout << "    ✓ Configuration Complete!" << ColorTheme::RESET << std::endl;
    ColorTheme::print_separator();

    std::cout << ColorTheme::CYAN << "\n  📋 Summary:\n" << ColorTheme::RESET;
    std::cout << "    Questions: " << questionCount << "\n";
    std::cout << "    Difficulty: " << difficulty << "\n";
    std::cout << "    Category: " << category << "\n";
    std::cout << "    Timer: " << (timerEnabled ? std::to_string(timerSeconds) + "s" : "Disabled") << "\n";
    std::cout << "    Lifelines: " << (lifelinesEnabled ? "Enabled" : "Disabled") << "\n";
    std::cout << "\n";
}

void ConfigurationUI::show_mode_config_info(Gamemode mode){
    std::cout << ColorTheme::YELLOW << "\n  ℹ️ Mode Configuration Info\n" << ColorTheme::RESET;
    switch(mode){
        case CLASSIC:
            std::cout << "    Classic mode - fully customizable\n";
            break;
        case QUICK_ATTACK:
            std::cout << "    Quick Attack - speed challenge, lifelines disabled\n";
            break;
        case SURVIVAL:
            std::cout << "    Survival - limited lives, increasing difficulty\n";
            break;
        case MARATHON:
            std::cout << "    Marathon - endurance test, all questions\n";
            break;
        case LIGHTNING:
            std::cout << "    Lightning - rapid fire questions\n";
            break;
        case PRACTICE:
            std::cout << "    Practice - no pressure, learn at your pace\n";
            break;
    }
}

void ConfigurationUI::show_timer_options(){
    std::cout << ColorTheme::CYAN << "\n[Timer Options]" << ColorTheme::RESET << std::endl;
    std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - No Timer(Practice)\n";
    std::cout << "    " << ColorTheme::YELLOW << "2" << ColorTheme::RESET << " - 60 seconds per question\n";
    std::cout << "    " << ColorTheme::RED << "3" << ColorTheme::RESET << " - 30 seconds per question\n";
    std::cout << "    " << ColorTheme::MAGENTA << "4" << ColorTheme::RESET << " - 15 seconds per question(Hard!)\n";
}

void ConfigurationUI::show_lifeline_options(){
    std::cout << ColorTheme::CYAN << "\n[Lifeline Options]" << ColorTheme::RESET << std::endl;
    std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - Enabled (50/50, SKIP)\n";
    std::cout << "    " << ColorTheme::RED << "2" << ColorTheme::RESET << " - Disabled (Hard Mode)\n";
}
