#include "ui/SaveGameUI.h"
#include "ui/ColorTheme.h"
#include <iostream>

void SaveGameUI::show_save_prompt(){
    std::cout << ColorTheme::YELLOW << "\n💾 Save your progress?\n" << ColorTheme::RESET;
    std::cout << "  [1] Yes, save game\n";
    std::cout << "  [2] No, discard progress\n";
}

void SaveGameUI::show_load_prompt(){
    std::cout << ColorTheme::YELLOW << "\n📂 A saved game was found!\n" << ColorTheme::RESET;
    std::cout << "  You can continue where you left off.\n";
    std::cout << ColorTheme::GREEN << "  [1]" << ColorTheme::RESET << " Continue Saved Game 📂\n";
    std::cout << ColorTheme::RED << "  [2]" << ColorTheme::RESET << " Start New Game (Erase Save) 🗑️\n"; 
}

void SaveGameUI::show_save_success(const std::string& filename){
    std::cout << ColorTheme::GREEN << "\n✓ Game saved successfully to " << filename << ColorTheme::RESET << std::endl;
}

void SaveGameUI::show_save_error(const std::string& message){
    std::cout << ColorTheme::RED << "\n✗ Save failed: " << message << ColorTheme::RESET << std::endl;
}

void SaveGameUI::show_load_success(){
    std::cout << ColorTheme::GREEN << "\n✓ Save loaded successfully!" << ColorTheme::RESET << std::endl;
}

void SaveGameUI::show_load_error(const std::string& message){
    std::cout << ColorTheme::RED << "\n✗ Load failed: " << message << ColorTheme::RESET << std::endl;
}
