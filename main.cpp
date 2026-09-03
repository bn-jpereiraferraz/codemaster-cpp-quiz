#include "QuizGame.h"
#include "ColorTheme.h"
#include "AsciiArt.h"
#include <iostream>

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

          std::cout << ColorTheme::CYAN << "    Choose option: "
                    << ColorTheme::RESET;

          int choice;
          std::cin >> choice;
          std::cin.ignore();  // Clear newline

          switch (choice) {
              case 1:  // Start New Quiz
                  // Step 1: Select game mode
                  game.show_game_mode_menu();

                  std::cout << ColorTheme::CYAN << "    Choose mode: "
                            << ColorTheme::RESET;
  
                  int modeChoice;
                  std::cin >> modeChoice;
                  std::cin.ignore();

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