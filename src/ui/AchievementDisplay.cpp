#include "ui/AchievementDisplay.h"
#include "ui/ColorTheme.h"
#include <iostream>

void AchievementDisplay::show_all_achievements(const std::vector<Achievement>& achievements){
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n🏆 ACHIEVEMENTS\n" << ColorTheme::RESET;
    ColorTheme::print_separator();

    for (const Achievement& a : achievements){
        if (a.unlocked){
            std::cout << ColorTheme::YELLOW << a.icon << " " << a.name << ColorTheme::RESET << "✓\n";
            std::cout << "  " << ColorTheme::DIM << a.description << ColorTheme::RESET << "\n";
            std::cout << "  Unlocked: " << a.dateUnlocked << "\n\n";
        }else{
            std::cout << ColorTheme::DIM << "🔒 " << a.name << " (Locked)\n";
            std::cout << "  " << a.description << ColorTheme::RESET << "\n\n";
        }
    }
}

void AchievementDisplay::show_unlocked_achievements(const std::vector<Achievement>& achievements){
    std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << "\n⭐ YOUR ACHIEVEMENTS\n" << ColorTheme::RESET;

    int count  = 0;
    for (const Achievement& a : achievements){
        if (a.unlocked){
            std::cout << ColorTheme::YELLOW << a.icon << " " << a.name << ColorTheme::RESET << "\n";
            std::cout << "  " << a.description << "\n";
            std::cout << "  " << ColorTheme::DIM << a.dateUnlocked << ColorTheme::RESET << "\n\n";
            count++;
        }
    }

    if (count == 0){
        std::cout << ColorTheme::DIM << "  No achievements yet. Keep Playing!\n" << ColorTheme::RESET;
    }
}

void AchievementDisplay::show_unlock_notfication(const Achievement& achievement){
    std::cout << "\n";
    ColorTheme::print_separator();
    std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << "    🎉 ACHIEVEMENT UNLOCKED! 🎉\n" << ColorTheme::RESET;
    std::cout << ColorTheme::YELLOW << "   " << achievement.icon << " " << achievement.name << ColorTheme::RESET << "\n";
    std::cout << "    " << ColorTheme::DIM << achievement.description << ColorTheme::RESET << "\n";
    ColorTheme::print_separator();
}

void AchievementDisplay::show_achievement_progress(const std::string& name, int current, int required){
    double percentage = (current * 100.0) / required;
    int barWidth = 20;
    int filled = (int)((percentage / 100.0) * barWidth);

    std::cout << "  " << name << ": [";

    for (int i = 0; i < barWidth; i++){
        if (i < filled) std::cout << "█";
        else std::cout << "░";
    }

    std::cout << "] " << current << "/" << required << "\n";
}