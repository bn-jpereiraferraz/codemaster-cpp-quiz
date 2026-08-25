#include "ColorTheme.h"
#include <iostream>

//===========================================
// COLOR THEME CLASS: Static Color Definitions
//===========================================

// Define all the static ANSI Color Codes
// These are escape sequences that terminals interpret as colors

const char* ColorTheme::RESET = "\033[0m";     // Reset to default
const char* ColorTheme::RED = "\033[31m";      // Red text
const char* ColorTheme::GREEN = "\033[32m";    // Green text
const char* ColorTheme::YELLOW = "\033[33m";   // Yellow text
const char* ColorTheme::BLUE = "\033[34m";     // Blue text
const char* ColorTheme::MAGENTA = "\033[35m";  // Magenta text
const char* ColorTheme::CYAN = "\033[36m";     // Cyan text
const char* ColorTheme::BOLD = "\033[1m";      // Bold text
const char* ColorTheme::DIM = "\033[2m";       // Dimmed text

// Print the game banner - called at the start
void ColorTheme::print_banner() {
    std::cout << CYAN << BOLD;
    std::cout << R"(
      ╔════════════════════════════════════════════════╗
      ║                                                ║
      ║     ██████╗ ██╗   ██╗██╗███████╗               ║
      ║    ██╔═══██╗██║   ██║██║╚══███╔╝               ║
      ║    ██║   ██║██║   ██║██║  ███╔╝                ║
      ║    ██║▄▄ ██║██║   ██║██║ ███╔╝                 ║
      ║    ╚██████╔╝╚██████╔╝██║███████╗               ║
      ║     ╚══▀▀═╝  ╚═════╝ ╚═╝╚══════╝               ║
      ║                                                ║
      ║           CODEMASTER C++ QUIZ                  ║
      ║        Test Your Programming Skills!           ║
      ║                                                ║
      ╚════════════════════════════════════════════════╝
      )" << RESET << std::endl;
}

// Print separator line
void ColorTheme::print_separator() {
    std::cout << DIM << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << std::endl;
}

// Print correct answer message with points
void ColorTheme::print_correct_message(int points) {
    std::cout << GREEN << BOLD << " ✓ CORRECT!" << RESET;
    std::cout << GREEN << "+" << points << " points" << RESET << std::endl;
}

// Print wrong answer message
void ColorTheme::print_wrong_message() {
    std::cout << RED << BOLD << " ✗ WRONG!" << RESET << std::endl;
}

// Print question header with number
void ColorTheme::print_question_header(int current, int total) {
    std::cout << "\n" << YELLOW << BOLD << "╔═══ Question " << current << " of " << total << " ═══╗" << RESET << std::endl;
}

// Print progress bar showing quiz completion
void ColorTheme::print_progress_bar(int current, int total) {
    int barWidth = 40;  // Width of the progress bar in characters
    float progress = (float)current / total;  // Percentage calculation

    std::cout << CYAN << "Progress [";

    // Calculate how many "filled" blocks to show
    int filled = barWidth * progress;

    // Draw progress bar
    for (int i = 0; i < barWidth; i++) {
        if (i < filled) {
            std::cout << "█";  // Filled block
        } else {
            std::cout << "░";  // Empty block
        }
    }

    // Show percentage of progress
    std::cout << "] " << int(progress * 100.0) << "%" << RESET << std::endl;
}
