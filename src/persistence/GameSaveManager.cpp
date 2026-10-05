#include "persistence/GameSaveManager.h"
#include "core/QuestionBank.h"
#include "core/GameExceptions.h"
#include "ui/ColorTheme.h"
#include <fstream>
#include <iostream>
#include <cstdio>

GameSaveManager::GameSaveManager() {
}

bool GameSaveManager::save(const std::string& filename,
                            const GameSession& session,
                            const GameConfiguration& config,
                            const Lifelines& lifelines) {
    try {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw FileException(filename, "Could not create save file");
        }

        writeHeader(file);
        writeSessionData(file, session);
        writeConfigData(file, config);
        writeLifelineData(file, lifelines);

        if (file.fail()) {
            throw SaveLoadException("Error writing to save file");
        }

        file.close();

        std::cout << ColorTheme::GREEN << "\n💾 Game saved successfully!"
                  << ColorTheme::RESET << std::endl;

    } catch (const GameException& e) {
        std::cerr << ColorTheme::RED << "Save error: " << e.what()
                  << ColorTheme::RESET << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << ColorTheme::RED << "Unexpected error during save: "
                  << e.what() << ColorTheme::RESET << std::endl;
        return false;
    }

    return true;
}

bool GameSaveManager::load(const std::string& filename,
                            GameSession& session,
                            GameConfiguration& config,
                            Lifelines& lifelines) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << ColorTheme::RED << "Error: Could not open save file!"
                  << ColorTheme::RESET << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t equals = line.find('=');
        if (equals == std::string::npos) continue;

        std::string key = line.substr(0, equals);
        std::string value = line.substr(equals + 1);

        parseKeyValue(key, value, session, config, lifelines);
    }

    file.close();

    std::cout << ColorTheme::GREEN << "\n💾 Game loaded successfully!"
              << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::CYAN << "Resuming at question "
              << (session.get_current_question_index() + 1)
              << " of " << config.get_question_count()
              << ColorTheme::RESET << std::endl;

    return true;
}

bool GameSaveManager::exists(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}

void GameSaveManager::deleteSave(const std::string& filename) {
    std::remove(filename.c_str());
    std::cout << ColorTheme::YELLOW << "💾 Save File Deleted."
              << ColorTheme::RESET << std::endl;
}

void GameSaveManager::writeHeader(std::ofstream& file) const {
    file << "# CodeMaster Quiz Save File\n";
    file << "VERSION=2.0\n";
}

void GameSaveManager::writeSessionData(std::ofstream& file, const GameSession& session) const {
    file << "\n# Progress\n";
    file << "CURRENT_QUESTION=" << session.get_current_question_index() << "\n";
    file << "\n# Scores\n";
    file << "EARNED_SCORE=" << session.get_earned_score() << "\n";
    file << "TOTAL_SCORE=" << session.get_total_score() << "\n";
    file << "CORRECT_COUNT=" << session.get_correct_count() << "\n";
    file << "\n# Streaks\n";
    file << "CURRENT_STREAK=" << session.get_current_streak() << "\n";
    file << "BEST_STREAK=" << session.get_best_streak() << "\n";
    file << "TOTAL_BONUS=" << session.get_total_bonus_points() << "\n";
}

void GameSaveManager::writeConfigData(std::ofstream& file, const GameConfiguration& config) const {
    file << "\n# Settings\n";
    file << "TOTAL_QUESTIONS=" << config.get_question_count() << "\n";
    file << "DIFFICULTY=" << DifficultyUtils::to_string(config.get_difficulty()) << "\n";
    file << "TIMER_ENABLED=" << (config.is_timer_enabled() ? "true" : "false") << "\n";
    file << "TIME_LIMIT=" << config.get_timer_seconds() << "\n";
    file << "LIFELINES_ENABLED=" << (config.are_lifelines_enabled() ? "true" : "false") << "\n";
}

void GameSaveManager::writeLifelineData(std::ofstream& file, const Lifelines& lifelines) const {
    file << "\n# Lifeline States\n";
    file << "LIFELINE_5050_USED=" << (lifelines.is_fifty_fifty_used() ? "true" : "false") << "\n";
    file << "LIFELINE_SKIP_USED=" << (lifelines.is_skip_used() ? "true" : "false") << "\n";
    file << "LIFELINE_HINT_USED=" << (lifelines.is_hint_used() ? "true" : "false") << "\n";
}

void GameSaveManager::parseKeyValue(const std::string& key, const std::string& value,
                                     GameSession& session, GameConfiguration& config,
                                     Lifelines& lifelines) {
    // Session data
    if (key == "CURRENT_QUESTION") {
        session.set_current_question_index(std::stoi(value));
    }
    else if (key == "EARNED_SCORE") {
        session.set_earned_score(std::stoi(value));
    }
    else if (key == "TOTAL_SCORE") {
        session.set_total_score(std::stoi(value));
    }
    else if (key == "CORRECT_COUNT") {
        session.set_correct_count(std::stoi(value));
    }
    else if (key == "CURRENT_STREAK") {
        session.set_current_streak(std::stoi(value));
    }
    else if (key == "BEST_STREAK") {
        session.set_best_streak(std::stoi(value));
    }
    else if (key == "TOTAL_BONUS") {
        session.set_total_bonus_points(std::stoi(value));
    }
    // Configuration data
    else if (key == "TOTAL_QUESTIONS") {
        config.set_question_count(std::stoi(value));
    }
    else if (key == "DIFFICULTY") {
        config.set_difficulty(static_cast<Difficulty>(std::stoi(value)));
    }
    else if (key == "TIMER_ENABLED") {
        // Timer seconds will be loaded separately
    }
    else if (key == "TIME_LIMIT") {
        int seconds = std::stoi(value);
        if (seconds > 0) {
            config.enable_timer(seconds);
        } else {
            config.disable_timer();
        }
    }
    else if (key == "LIFELINES_ENABLED") {
        if (value == "true") {
            config.enable_lifelines();
        } else {
            config.disable_lifelines();
        }
    }
    // Lifeline states
    else if (key == "LIFELINE_5050_USED") {
        lifelines.set_fifty_fifty_used(value == "true");
    }
    else if (key == "LIFELINE_SKIP_USED") {
        lifelines.set_skip_used(value == "true");
    }
    else if (key == "LIFELINE_HINT_USED") {
        lifelines.set_hint_used(value == "true");
    }
}
