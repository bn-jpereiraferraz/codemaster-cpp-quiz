#include "core/GameRunner.h"
#include "core/Constants.h"
#include "core/GameExceptions.h"
#include "ui/ColorTheme.h"
#include "ui/AsciiArt.h"
#include "utils/InputValidator.h"
#include <iostream>

GameRunner::GameRunner() : running(true) {
    try {
        // Try multiple paths for questions file
        bool loaded = false;

        // Path 1: Running from project root
        if (game.load_from_file(GameConstants::DEFAULT_QUESTIONS_FILE)) {
            loaded = true;
        }
        // Path 2: Running from build directory
        else if (game.load_from_file(GameConstants::FALLBACK_QUESTIONS_FILE)) {
            loaded = true;
        }

        if (!loaded) {
            std::cout << ColorTheme::YELLOW
                      << "⚠️  Could not load questions.txt, using default questions"
                      << ColorTheme::RESET << std::endl;
            game.load_default_questions();
        }

        // Verify we have questions
        if (!game.get_question_bank().has_questions()) {
            throw InvalidStateException("No questions available to play!");
        }

    } catch (const GameException& e) {
        std::cerr << ColorTheme::RED << "Game initialization error: "
                  << e.what() << ColorTheme::RESET << std::endl;
        throw;  // Re-throw to be handled by main
    } catch (const std::exception& e) {
        std::cerr << ColorTheme::RED << "Unexpected error during initialization: "
                  << e.what() << ColorTheme::RESET << std::endl;
        throw;
    }
}

void GameRunner::run() {
    AsciiArt::display_main_logo();
    std::cout << std::endl;

    while (running) {
        handle_main_menu();
    }
}

void GameRunner::handle_main_menu() {
    menuController.showMainMenu();

    int choice = InputValidator::get_menu_choice("    Choose option: ", 4);

    switch (choice) {
        case 1: handle_new_quiz(); break;
        case 2: handle_configure_settings(); break;
        case 3: handle_view_statistics(); break;
        case 4: handle_exit(); break;
        default:
            std::cout << ColorTheme::RED << "\n❌ Invalid choice!"
                      << ColorTheme::RESET << std::endl;
    }
}

void GameRunner::handle_new_quiz() {
    try {
        Gamemode mode = menuController.selectGameMode();
        game.get_configuration().set_game_mode(mode);

        if (menuController.promptLoadSave(game, GameConstants::DEFAULT_SAVE_FILE)) {
            game.run();
        } else {
            menuController.configureGame(game);
            game.run();
        }

        resultsManager.displayResults(game);
        resultsManager.displayAchievements(game);

    } catch (const SaveLoadException& e) {
        std::cerr << ColorTheme::RED << "Save/Load error: " << e.what()
                  << ColorTheme::RESET << std::endl;
        std::cout << "Starting new game instead..." << std::endl;
        menuController.configureGame(game);
        game.run();
    } catch (const GameException& e) {
        std::cerr << ColorTheme::RED << "Game error: " << e.what()
                  << ColorTheme::RESET << std::endl;
    } catch (const std::exception& e) {
        std::cerr << ColorTheme::RED << "Unexpected error: " << e.what()
                  << ColorTheme::RESET << std::endl;
    }
}

void GameRunner::handle_configure_settings() {
    menuController.configureGame(game);
}

void GameRunner::handle_view_statistics() {
    menuController.showStatisticsMenu(game);
}

void GameRunner::handle_exit() {
    std::cout << ColorTheme::GREEN << "\n👋 Thanks for playing!"
              << ColorTheme::RESET << std::endl;
    running = false;
}
