#include "controllers/MenuController.h"
#include "ui/MenuSystem.h"
#include "ui/ConfigurationUI.h"
#include "ui/StatisticsMenu.h"
#include "ui/SaveGameUI.h"
#include "ui/ColorTheme.h"
#include "utils/InputValidator.h"
#include "persistence/GameSaveManager.h"
#include "core/Constants.h"
#include <iostream>

MenuController::MenuController() {
}

void MenuController::showMainMenu() {
    std::vector<MenuItem> items = {
        MenuItem("Start New Quiz", ColorTheme::GREEN),
        MenuItem("Configure Settings", ColorTheme::YELLOW),
        MenuItem("View Statistics 📊", ColorTheme::CYAN),
        MenuItem("Exit Game", ColorTheme::RED)
    };
    MenuSystem::show_menu("🎮 MAIN MENU 🎮", items);
}

void MenuController::showGameModeMenu() {
    std::vector<MenuItem> items = {
        MenuItem("🎯 Classic Mode", ColorTheme::GREEN),
        MenuItem("⚡ Quick Attack", ColorTheme::YELLOW),
        MenuItem("💀 Survival Mode", ColorTheme::RED),
        MenuItem("🏃 Marathon Mode", ColorTheme::MAGENTA),
        MenuItem("⚡ Lightning Round", ColorTheme::CYAN),
        MenuItem("📚 Practice Mode", ColorTheme::BLUE)
    };
    MenuSystem::show_menu("🎮 SELECT GAME MODE 🎮", items);
}

Gamemode MenuController::selectGameMode() {
    showGameModeMenu();
    int modeChoice = InputValidator::get_menu_choice("    Choose mode: ", 6);

    switch(modeChoice) {
        case 1: return Gamemode::Classic;
        case 2: return Gamemode::QuickAttack;
        case 3: return Gamemode::Survival;
        case 4: return Gamemode::Marathon;
        case 5: return Gamemode::Lightning;
        case 6: return Gamemode::Practice;
        default:
            std::cout << ColorTheme::RED << "Invalid choice! Defaulting to Classic."
                      << ColorTheme::RESET << std::endl;
            return Gamemode::Classic;
    }
}

void MenuController::configureGame(IGameState& game) {
    ConfigurationUI::show_header();

    configureQuestionCount(game);
    configureDifficulty(game);
    configureCategory(game);
    configureTimer(game);
    configureLifelines(game);

    ConfigurationUI::show_complete();
}

void MenuController::configureQuestionCount(IGameState& game) {
    int count = ConfigurationUI::prompt_question_count(game.get_configuration().get_game_mode());
    game.get_configuration().set_question_count(count);
}

void MenuController::configureDifficulty(IGameState& game) {
    int diffChoice = ConfigurationUI::prompt_difficulty();
    switch(diffChoice) {
        case 1: game.get_configuration().set_difficulty(Difficulty::Easy); break;
        case 2: game.get_configuration().set_difficulty(Difficulty::Medium); break;
        case 3: game.get_configuration().set_difficulty(Difficulty::Hard); break;
        case 4:
        default: game.get_configuration().set_difficulty(Difficulty::Mixed); break;
    }
}

void MenuController::configureCategory(IGameState& game) {
    int categoryChoice = ConfigurationUI::prompt_category();
    game.get_configuration().set_category(categoryChoice == 1 ? GameConstants::CATEGORY_ALL : "Filtered");
}

void MenuController::configureTimer(IGameState& game) {
    int timerChoice = ConfigurationUI::prompt_timer(game.get_configuration().get_game_mode());
    if (timerChoice == -1) {
        game.get_configuration().enable_timer(10);
    } else if (timerChoice == -2 || timerChoice == 0) {
        game.get_configuration().disable_timer();
    } else {
        switch(timerChoice) {
            case 1: game.get_configuration().disable_timer(); break;
            case 2: game.get_configuration().enable_timer(60); break;
            case 3: game.get_configuration().enable_timer(30); break;
            case 4: game.get_configuration().enable_timer(15); break;
            default: game.get_configuration().disable_timer(); break;
        }
    }
}

void MenuController::configureLifelines(IGameState& game) {
    int lifelineChoice = ConfigurationUI::prompt_lifelines(game.get_configuration().get_game_mode());
    if (lifelineChoice == 1) {
        game.get_configuration().enable_lifelines();
        game.get_lifelines().reset();
    } else {
        game.get_configuration().disable_lifelines();
    }
}

bool MenuController::promptLoadSave(IGameState& game, const std::string& saveFilename) {
    GameSaveManager saveManager;

    if (!saveManager.exists(saveFilename)) {
        return false;
    }

    SaveGameUI::show_load_prompt();
    int choice = InputValidator::get_menu_choice("    Your choice: ", 2);

    if (choice == 1) {
        if (saveManager.load(saveFilename, game.get_session(),
                             game.get_configuration(), game.get_lifelines())) {
            SaveGameUI::show_load_success();
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.get();
            return true;
        } else {
            SaveGameUI::show_load_error("Could not load save file");
            return false;
        }
    } else {
        saveManager.deleteSave(saveFilename);
        std::cout << ColorTheme::YELLOW << "\n    🗑️   Save deleted. Starting fresh!"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
        std::cin.get();
        return false;
    }
}

void MenuController::showStatisticsMenu(IGameState& game) {
    while (true) {
        StatisticsMenu::show_statistics_menu();
        int choice = InputValidator::get_menu_choice("\n👉 Enter your choice (1-5): ", 5);

        if (choice == 5) {
            return;
        }

        handleStatisticsMenuChoice(choice, game);
    }
}

void MenuController::handleStatisticsMenuChoice(int choice, IGameState& game) {
    switch (choice) {
        case 1:
            game.get_statistics().display_career_stats();
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.ignore();
            std::cin.get();
            break;

        case 2: {
            StatisticsMenu::show_mode_selection();
            int modeChoice = InputValidator::get_menu_choice("\n👉 Choose mode (1-6): ", 6);
            game.get_statistics().display_mode_stats(static_cast<Gamemode>(modeChoice - 1));
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 3:
            game.get_statistics().display_category_stats();
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.ignore();
            std::cin.get();
            break;

        case 4: {
            StatisticsMenu::show_mode_selection();
            int modeChoice = InputValidator::get_menu_choice("\n👉 Choose mode (1-6): ", 6);
            game.get_statistics().display_high_scores(static_cast<Gamemode>(modeChoice - 1));
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.ignore();
            std::cin.get();
            break;
        }

        default:
            std::cout << ColorTheme::RED << "❌ Invalid choice! Please select 1-5.\n" << ColorTheme::RESET;
            break;
    }
}
