#include "ui/StatisticsMenu.h"
#include "ui/ColorTheme.h"
#include <iostream>

void StatisticsMenu::show_statistics_menu(){
    std::cout << "\n\n";
    ColorTheme::print_separator();
    ColorTheme::print_separator();

    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n    📊 STATISTICS MENU\n" << ColorTheme::RESET;
    std::cout << "\n";

    std::cout << ColorTheme::GREEN << "    ▸ " << ColorTheme::BOLD << "[1]" << ColorTheme::RESET << ColorTheme::GREEN << " Career Statistics" << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::YELLOW << "    ▸ " << ColorTheme::BOLD << "[2]" << ColorTheme::RESET << ColorTheme::YELLOW << " Mode Statistics" << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::CYAN << "    ▸ " << ColorTheme::BOLD << "[3]" << ColorTheme::RESET << ColorTheme::CYAN << " Category Performance" << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::MAGENTA << "    ▸ " << ColorTheme::BOLD << "[4]" << ColorTheme::RESET << ColorTheme::MAGENTA << " High Scores" << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::RED << "    ▸ " << ColorTheme::BOLD << "[5]" << ColorTheme::RESET << ColorTheme::RED << " Back to Main Menu" << ColorTheme::RESET << std::endl;
    
    std::cout << "\n";
    ColorTheme::print_separator();
}

void StatisticsMenu::show_mode_selection(){
    std::cout << ColorTheme::CYAN << "\n📊 Select Mode:\n" << ColorTheme::RESET;
    std::cout << "  [1] Classic\n";
    std::cout << "  [2] Quick Attack\n";
    std::cout << "  [3] Survival\n";
    std::cout << "  [4] Marathon\n";
    std::cout << "  [5] Lightning\n";
    std::cout << "  [6] Practice\n";
}

void StatisticsMenu::show_category_selection(){
    std::cout << ColorTheme::CYAN << "\n📂 Select Category:\n" << ColorTheme::RESET;
    std::cout << "  [1] All Categories\n";
    std::cout << "  [2] Basics\n";
    std::cout << "  [3] OOP\n";
    std::cout << "  [4] Pointers & Memory\n";
    std::cout << "  [5] STL\n";
    std::cout << "  [6] Advanced\n";
}

