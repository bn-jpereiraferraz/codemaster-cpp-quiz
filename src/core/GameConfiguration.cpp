#include "core/GameConfiguration.h"
#include "core/Constants.h"
#include "modes/ModeSetup.h"

GameConfiguration::GameConfiguration()
    : gameMode(Gamemode::Classic),
      difficulty(Difficulty::Mixed),
      questionCount(GameConstants::DEFAULT_QUESTION_COUNT),
      timerEnabled(false),
      timerSeconds(GameConstants::DEFAULT_TIMER_SECONDS),
      lifelinesEnabled(false),
      selectedCategory(GameConstants::CATEGORY_ALL) {
}

GameConfiguration GameConfiguration::for_mode(Gamemode mode) {
    GameConfiguration config;
    config.gameMode = mode;
    config.questionCount = ModeSetup::get_question_count(mode);
    config.timerEnabled = ModeSetup::is_timer_enabled(mode);
    config.timerSeconds = ModeSetup::get_timer_seconds(mode);
    config.lifelinesEnabled = ModeSetup::are_lifelines_enabled(mode);
    return config;
}

void GameConfiguration::set_game_mode(Gamemode mode) {
    gameMode = mode;
}

void GameConfiguration::set_difficulty(Difficulty diff) {
    difficulty = diff;
}

void GameConfiguration::set_question_count(int count) {
    if (count < 50) count = 50;
    if (count > 300) count = 300;
    questionCount = count;
}

void GameConfiguration::set_category(const std::string& category) {
    selectedCategory = category;
}

void GameConfiguration::enable_timer(int seconds) {
    timerEnabled = true;
    timerSeconds = seconds;
}

void GameConfiguration::disable_timer() {
    timerEnabled = false;
}

void GameConfiguration::enable_lifelines() {
    lifelinesEnabled = true;
}

void GameConfiguration::disable_lifelines() {
    lifelinesEnabled = false;
}

Gamemode GameConfiguration::get_game_mode() const {
    return gameMode;
}

Difficulty GameConfiguration::get_difficulty() const {
    return difficulty;
}

int GameConfiguration::get_question_count() const {
    return questionCount;
}

std::string GameConfiguration::get_category() const {
    return selectedCategory;
}

bool GameConfiguration::is_timer_enabled() const {
    return timerEnabled;
}

int GameConfiguration::get_timer_seconds() const {
    return timerSeconds;
}

bool GameConfiguration::are_lifelines_enabled() const {
    return lifelinesEnabled;
}

bool GameConfiguration::is_valid() const {
    return questionCount >= 50 && questionCount <= 300;
}
