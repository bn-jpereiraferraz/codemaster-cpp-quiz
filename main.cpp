#include <iostream>
#include "quiz.h"

int main() {
    QuizGame game;
  
    // Load questions from file
    if (!game.load_from_file("questions.txt")) {
        game.load_default_questions();  // Fallback
    }

    // Main menu loop
    bool running = true;
    while (running) {
        game.show_main_menu();

        std::cout << ColorTheme::CYAN << "    Choose option: "
                  << ColorTheme::RESET;

        int choice;
        std::cin >> choice;
        std::cin.ignore();  // Clear newline

        switch (choice) {
            case 1:  // Start New Quiz
                // Check for saved game
                if (game.prompt_load_save()) {
                    // Loaded save, just run
                    game.run();
                } else {
                    // New game - configure first
                    game.configure_game();
                    game.run();
                }
                break;

            case 2:  // Configure Settings
                game.configure_game();
                break;

            case 3:  // Exit
                std::cout << ColorTheme::GREEN << "\n👋 Thanks for playing!"
                          << ColorTheme::RESET << std::endl;
                running = false;
                break;

            default:
                std::cout << ColorTheme::RED << "\n❌ Invalid choice!"
                          << ColorTheme::RESET << std::endl;
        }
    }

    return 0;
}