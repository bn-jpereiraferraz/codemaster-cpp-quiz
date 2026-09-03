#include "AsciiArt.h"
#include "ColorTheme.h"
#include <iostream>

//MAIN BRANDING  - CODEMASTER LOGO
void AsciiArt::display_main_logo(){
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << R"(    
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║   ██████╗ ██████╗ ██████╗ ███████╗███╗   ███╗ █████╗ ███████╗ ║
    ║  ██╔════╝██╔═══██╗██╔══██╗██╔════╝████╗ ████║██╔══██╗██╔════╝ ║
    ║  ██║     ██║   ██║██║  ██║█████╗  ██╔████╔██║███████║███████╗ ║
    ║  ██║     ██║   ██║██║  ██║██╔══╝  ██║╚██╔╝██║██╔══██║╚════██║ ║
    ║  ╚██████╗╚██████╔╝██████╔╝███████╗██║ ╚═╝ ██║██║  ██║███████║ ║
    ║   ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝ ║
    ║                                                               ║
    ║              🎯  C++ QUIZ MASTERY CHALLENGE  🎯               ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝)"
    << ColorTheme::RESET << std::endl;
}

//CLASSIC MODE BANNER
void AsciiArt::display_classic_banner(){
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << R"(    
    ╔════════════════════════════════════════════╗
    ║                                            ║
    ║     ⭐  CLASSIC MODE  ⭐                   ║
    ║                                            ║
    ║   The Original Quiz Experience             ║
    ║   Configure Your Perfect Challenge         ║
    ║                                            ║
    ╚════════════════════════════════════════════╝)"
    << ColorTheme::RESET << std::endl;
}

//QUICK ATTACK BANNER
void AsciiArt::display_quick_attack_banner(){
    std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << R"(      
      ╔════════════════════════════════════════════╗
      ║                                            ║
      ║     ⚡⚡⚡  QUICK ATTACK  ⚡⚡⚡           ║
      ║                                            ║
      ║   5 Minutes  |  Wrong = -15 Seconds        ║
      ║   Speed is Everything!                     ║
      ║                                            ║
      ╚════════════════════════════════════════════╝)" 
      << ColorTheme::RESET << std::endl;
}

//SURVIVAL BANNER
void AsciiArt::display_survival_banner(){
    std::cout << ColorTheme::RED << ColorTheme::BOLD;
    std::cout << R"(      
      ╔════════════════════════════════════════════╗
      ║                                            ║
      ║     💀  SURVIVAL MODE  💀                  ║
      ║                                            ║
      ║   3 Lives  |  1 Wrong = 1 Life Lost        ║
      ║   Can You Stay Alive?                      ║
      ║                                            ║
      ╚════════════════════════════════════════════╝)" 
      << ColorTheme::RESET << std::endl;
}

//MARATHON BANNER
void AsciiArt::display_marathon_banner(){
    std::cout << ColorTheme::MAGENTA << ColorTheme::BOLD;
    std::cout << R"(      
      ╔════════════════════════════════════════════╗
      ║                                            ║
      ║     🏃  MARATHON MODE  🏃                  ║
      ║                                            ║
      ║   ALL 300 Questions  |  No Shortcuts       ║
      ║   The Ultimate Endurance Test              ║
      ║                                            ║
      ╚════════════════════════════════════════════╝)" 
    << ColorTheme::RESET << std::endl;
}

//LIGHTNING BANNER
void AsciiArt::display_lightning_banner(){
    std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << R"(      
      ╔════════════════════════════════════════════╗
      ║                                            ║
      ║     ⚡⚡⚡  LIGHTNING ROUND  ⚡⚡⚡        ║
      ║                                            ║
      ║   10 Seconds Per Question  |  No Mercy     ║
      ║   Think Fast or Die!                       ║
      ║                                            ║
      ╚════════════════════════════════════════════╝)" 
    << ColorTheme::RESET << std::endl;
}

//PRACTICE BANNER
void AsciiArt::display_practice_banner(){
    std::cout << ColorTheme::GREEN << ColorTheme::BOLD;
    std::cout << R"(      
      ╔════════════════════════════════════════════╗
      ║                                            ║
      ║     📚  PRACTICE MODE  📚                  ║
      ║                                            ║
      ║   No Pressure  |  Learn at Your Pace       ║
      ║   See Correct Answers                      ║
      ║                                            ║
      ╚════════════════════════════════════════════╝)" 
      << ColorTheme::RESET << std::endl;
}

//PERFECT VICTORY = 100%
void AsciiArt::display_perfect_victory(){
    std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << R"(    
    ╔════════════════════════════════════════════════════════╗
    ║                                                        ║
    ║   ⭐⭐⭐  PERFECT SCORE - FLAWLESS VICTORY!  ⭐⭐⭐   ║
    ║                                                        ║
    ║          🏆    🎯    100%    🎯    🏆                 ║
    ║                                                        ║
    ║              YOU ARE A CODEMASTER!                     ║
    ║                                                        ║
    ╚════════════════════════════════════════════════════════╝)" 
    << ColorTheme::RESET << std::endl;
}

//GREAT VICTORY = 80%+
void AsciiArt::display_great_victory(){
    std::cout << ColorTheme::GREEN << ColorTheme::BOLD;
    std::cout << R"(    
    ╔═══════════════════════════════════════════╗
    ║                                           ║
    ║     ⭐⭐⭐  EXCELLENT WORK!  ⭐⭐⭐       ║
    ║                                           ║
    ║            🎯  Great Score!  🎯           ║
    ║                                           ║
    ║        You've Mastered the Material!      ║
    ║                                           ║
    ╚═══════════════════════════════════════════╝)" 
    << ColorTheme::RESET << std::endl;
}

//GOOD VICTORY = 60%+
void AsciiArt::display_good_victory(){
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << R"(      
      ╔═══════════════════════════════════════════╗
      ║                                           ║
      ║        ⭐  QUIZ COMPLETED!  ⭐            ║
      ║                                           ║
      ║            👍  Good Job!  👍              ║
      ║                                           ║
      ║         Keep Practicing to Improve!       ║
      ║                                           ║
      ╚═══════════════════════════════════════════╝)" 
    << ColorTheme::RESET << std::endl;
}

//GAMEOVER
void AsciiArt::display_game_over(){
    std::cout << ColorTheme::RED << ColorTheme::BOLD;
    std::cout << R"(      
      ╔═══════════════════════════════════════════╗
      ║                                           ║
      ║         💀  GAME OVER  💀                 ║
      ║                                           ║
      ║          Don't Give Up!                   ║
      ║                                           ║
      ║     Every Attempt Makes You Stronger 💪   ║
      ║                                           ║
      ╚═══════════════════════════════════════════╝)" 
    << ColorTheme::RESET << std::endl;
}

//===================
//DECORATIVE ELEMENTS
//===================
//TROPHY
void AsciiArt::display_trophy(){
    std::cout <<ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << R"(    
         ___________
        '._==_==_=_.'
        .-\:      /-.
       | (|:.     |) |
        '-|:.     |-'
          \::.    /
           '::. .'
             ) (
           _.' '._
          `"""""""`)"
    << ColorTheme::RESET << std::endl;
}

//SEPARATOR THICK - 1 LINES
void AsciiArt::display_seperator_thick(){
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "    ════════════════════════════════════════════════════════"
    << std::endl;
    std::cout << ColorTheme::RESET;
}

//SEPARATOR DOUBLE - 2 LINES
void AsciiArt::display_separator_double(){
    std::cout << ColorTheme::MAGENTA << ColorTheme::BOLD;
    std::cout << "    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    << std::endl;
    std::cout << "    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    << std::endl;
    std::cout << ColorTheme::RESET;
}