#include "ui/MenuSystem.h"
#include "ui/ColorTheme.h"
#include <iostream>

void MenuSystem::show_menu(const std::string& title, const std::vector<MenuItem>& items){
    std::cout << "\n\n";
    ColorTheme::print_separator();
    ColorTheme::print_separator();

    show_title(title);

    for (size_t i = 0; i < items.size(); i++){
        std::string color = items[i].color.empty() ? ColorTheme::GREEN : items[i].color;
        std::cout << color << "     ▸" << ColorTheme::BOLD << "[" << (i + 1) << "]"
        << ColorTheme::RESET << color << " " << items[i].label << ColorTheme::RESET << std::endl;
    }

    std::cout << "\n";
    ColorTheme::print_separator();
}

void MenuSystem::show_simple_menu(const std::string& title, const std::vector<std::string>& options){
    std::cout << ColorTheme::CYAN << "\n" << title << "\n" << ColorTheme::RESET;

    for (size_t i = 0; i < options.size(); i++){
        std::cout << "   [" << (i + 1) << "]" << options[i] << "\n";
    }    
}

void MenuSystem::show_title(const std::string& title){
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n";
    std::cout << "    ╔═══════════════════════════════════════╗\n";
    std::cout << "    ║                                       ║\n";
    std::cout << "    ║" << title;

    //pad to center
    int padding = 36 - title.length();
    for (int i = 0; i < padding; i++){
        std::cout << " ";
    }
    
    std::cout << "║\n";
    std::cout << "    ║                                       ║\n";
    std::cout << "    ╚═══════════════════════════════════════╝\n";
    std::cout << ColorTheme::RESET << "\n";
}

int MenuSystem::calculate_box_width(const std::string& text){
    return text.length() + 4;
}