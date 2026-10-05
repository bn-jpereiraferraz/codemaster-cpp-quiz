#include "ui/ConfigurationUI.h"
#include "ui/ColorTheme.h"
#include "utils/InputValidator.h"
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
        case Gamemode::Classic:
            std::cout << "    Classic mode - fully customizable\n";
            break;
        case Gamemode::QuickAttack:
            std::cout << "    Quick Attack - speed challenge, lifelines disabled\n";
            break;
        case Gamemode::Survival:
            std::cout << "    Survival - limited lives, increasing difficulty\n";
            break;
        case Gamemode::Marathon:
            std::cout << "    Marathon - endurance test, all questions\n";
            break;
        case Gamemode::Lightning:
            std::cout << "    Lightning - rapid fire questions\n";
            break;
        case Gamemode::Practice:
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

void ConfigurationUI::show_header(){
    std::cout << "\n";
    ColorTheme::print_separator();
    std::cout << ColorTheme::MAGENTA << ColorTheme::BOLD;
    std::cout << "\n    ⚙️   GAME CONFIGURATION ⚙️ \n" << ColorTheme::RESET;
    ColorTheme::print_separator();
}

int ConfigurationUI::prompt_question_count(Gamemode mode){
    if (mode == Gamemode::Marathon) {
        std::cout << ColorTheme::CYAN << "\n[1] Question Count" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::YELLOW << "🏃 Marathon Mode: ALL 300 questions (FIXED)"
                  << ColorTheme::RESET << std::endl;
        return 300;
    } else {
        std::cout << ColorTheme::CYAN << "\n[1] Question Count" << ColorTheme::RESET << std::endl;
        std::cout << "    Choose: ";
        std::cout << ColorTheme::DIM << "50 | 100 | 150 | 200 | 250 | 300" << ColorTheme::RESET << std::endl;
        return InputValidator::get_int_in_range("    Your choice: ", 50, 300);
    }
}

int ConfigurationUI::prompt_difficulty(){
    std::cout << ColorTheme::CYAN << "\n[2] Difficulty Level" << ColorTheme::RESET << std::endl;
    std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - Easy (5 pts)\n";
    std::cout << "    " << ColorTheme::YELLOW << "2" << ColorTheme::RESET << " - Medium (10 pts)\n";
    std::cout << "    " << ColorTheme::RED << "3" << ColorTheme::RESET << " - Hard (15 pts)\n";
    std::cout << "    " << ColorTheme::CYAN << "4" << ColorTheme::RESET << " - Mixed (All)\n";
    return InputValidator::get_menu_choice("    Your choice: ", 4);
}

int ConfigurationUI::prompt_category(){
    std::cout << ColorTheme::CYAN << "\n[3] Category Filter" << ColorTheme::RESET << std::endl;
    std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - All Categories (Mixed)\n";
    std::cout << "    " << ColorTheme::CYAN << "2" << ColorTheme::RESET << " - Basics\n";
    std::cout << "    " << ColorTheme::CYAN << "3" << ColorTheme::RESET << " - OOP (Object-Oriented)\n";
    std::cout << "    " << ColorTheme::CYAN << "4" << ColorTheme::RESET << " - Pointers & Memory\n";
    std::cout << "    " << ColorTheme::CYAN << "5" << ColorTheme::RESET << " - STL & Algorithms\n";
    std::cout << "    " << ColorTheme::CYAN << "6" << ColorTheme::RESET << " - Templates\n";
    std::cout << "    " << ColorTheme::CYAN << "7" << ColorTheme::RESET << " - Modern C++ (C++11+)\n";
    return InputValidator::get_menu_choice("    Your choice: ", 7);
}

int ConfigurationUI::prompt_timer(Gamemode mode){
    if (mode == Gamemode::Lightning) {
        std::cout << ColorTheme::CYAN << "\n[4] Timer Mode" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::YELLOW << "⚡ Lightning Mode: 10 seconds per question (FIXED)"
                  << ColorTheme::RESET << std::endl;
        return -1;  // Special value for Lightning
    } else if (mode == Gamemode::QuickAttack) {
        std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::YELLOW << "🏃 Quick Attack: 5-minute countdown (FIXED)"
                  << ColorTheme::RESET << std::endl;
        return -2;  // Special value for Quick Attack
    } else if (mode == Gamemode::Practice) {
        std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::GREEN << "📚 Practice Mode: No timer (learn at your pace)"
                  << ColorTheme::RESET << std::endl;
        return 0;  // 0 = disabled
    } else if (mode == Gamemode::Marathon) {
        std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::MAGENTA << "🏃 Marathon Mode: Tracks total session time (no per-question limit)"
                  << ColorTheme::RESET << std::endl;
        return 0;  // 0 = disabled
    } else {
        std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - No Timer (Practice)\n";
        std::cout << "    " << ColorTheme::YELLOW << "2" << ColorTheme::RESET << " - 60 seconds per question\n";
        std::cout << "    " << ColorTheme::RED << "3" << ColorTheme::RESET << " - 30 seconds per question\n";
        std::cout << "    " << ColorTheme::MAGENTA << "4" << ColorTheme::RESET << " - 15 seconds per question(Hard!)\n";
        return InputValidator::get_menu_choice("    Your choice: ", 4);
    }
}

int ConfigurationUI::prompt_lifelines(Gamemode mode){
    if (mode == Gamemode::Practice) {
        std::cout << ColorTheme::CYAN << "\n[5] Lifelines" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::GREEN << "📚 Practice Mode: Lifelines disabled (you'll see correct answers anyway)"
                  << ColorTheme::RESET << std::endl;
        return 2;  // Disabled
    } else if (mode == Gamemode::QuickAttack) {
        std::cout << ColorTheme::CYAN << "\n[4] Lifelines" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::YELLOW << "🏃 Quick Attack: Lifelines disabled (speed is key!)"
                  << ColorTheme::RESET << std::endl;
        return 2;  // Disabled
    } else {
        std::cout << ColorTheme::CYAN << "\n[4] Lifelines" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - Enabled (50/50, Skip)\n";
        std::cout << "    " << ColorTheme::RED << "2" << ColorTheme::RESET << " - Disabled (Hard Mode)\n";
        return InputValidator::get_menu_choice("    Your choice: ", 2);
    }
}

void ConfigurationUI::show_complete(){
    std::cout << "\n";
    ColorTheme::print_separator();
    std::cout << ColorTheme::GREEN << ColorTheme::BOLD;
    std::cout << "    ✓ Configuration Complete!" << ColorTheme::RESET << std::endl;
    ColorTheme::print_separator();
    std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
    std::cin.get();
}
