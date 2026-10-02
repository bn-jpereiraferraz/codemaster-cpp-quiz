#include "core/QuizGame.h"
#include "ui/ColorTheme.h"
#include "ui/AsciiArt.h"
#include <iostream>
#include "utils/InputValidator.h"

  int main() {

    AsciiArt::display_main_logo();
    std::cout << std::endl;
    
      QuizGame game;

      // Load questions from file
      if (!game.load_from_file("questions.txt")) {
          game.load_default_questions();  // Fallback
      }
  
      // Main menu loop
      bool running = true;
      while (running) {
          game.show_main_menu();

          int choice = InputValidator::get_menu_choice("    Choose option: ", 4);
        
          switch (choice) {
              case 1: {  // Start New Quiz
                  // Step 1: Select game mode
                  game.show_game_mode_menu();

                  int modeChoice = InputValidator::get_menu_choice("    Choose mode: ", 6);

                  // Set game mode based on choice
                  switch(modeChoice) {
                      case 1: game.set_game_mode(CLASSIC); break;
                      case 2: game.set_game_mode(QUICK_ATTACK); break;
                      case 3: game.set_game_mode(SURVIVAL); break;
                      case 4: game.set_game_mode(MARATHON); break;
                      case 5: game.set_game_mode(LIGHTNING); break;
                      case 6: game.set_game_mode(PRACTICE); break;
                      default:
                          std::cout << ColorTheme::RED << "Invalid choice! Defaulting to Classic."
                                    << ColorTheme::RESET << std::endl;
                          game.set_game_mode(CLASSIC);
                  }

                  // Step 2: Check for saved game
                  if (game.prompt_load_save()) {
                      // Loaded save, just run
                      game.run();
                  } else {
                      // New game - configure if Classic mode
                      // (Other modes have preset configurations)
                      // For now, always configure
                      game.configure_game();
                      game.run();
                  }
                  break;
              }

              case 2:  // Configure Settings
                  game.configure_game();
                  break;

              case 3:  // View Statistics
                  game.show_statistics_menu();
                  break;

              case 4:  // Exit
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