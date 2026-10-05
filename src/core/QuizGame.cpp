#include "core/QuizGame.h"
#include "core/Constants.h"
#include "modes/GameModes.h"
#include "ui/ColorTheme.h"
#include <iostream>

QuizGame::QuizGame()
    : questionBank(),
      session(),
      config(),
      globalTimer(GameConstants::DEFAULT_TIMER_SECONDS),
      lives(GameConstants::DEFAULT_LIVES)
{
    stats.load_from_file(GameConstants::STATISTICS_FILE);
}

QuizGame::~QuizGame() {
}

// IGameState Interface Implementation
QuestionBank& QuizGame::get_question_bank() {
    return questionBank;
}

const QuestionBank& QuizGame::get_question_bank() const {
    return questionBank;
}

GameSession& QuizGame::get_session() {
    return session;
}

const GameSession& QuizGame::get_session() const {
    return session;
}

GameConfiguration& QuizGame::get_configuration() {
    return config;
}

const GameConfiguration& QuizGame::get_configuration() const {
    return config;
}

Lifelines& QuizGame::get_lifelines() {
    return lifelines;
}

const Lifelines& QuizGame::get_lifelines() const {
    return lifelines;
}

Lives& QuizGame::get_lives() {
    return lives;
}

const Lives& QuizGame::get_lives() const {
    return lives;
}

GlobalTimer& QuizGame::get_global_timer() {
    return globalTimer;
}

const GlobalTimer& QuizGame::get_global_timer() const {
    return globalTimer;
}

Statistics& QuizGame::get_statistics() {
    return stats;
}

const Statistics& QuizGame::get_statistics() const {
    return stats;
}

void QuizGame::load_default_questions() {
    questionBank.load_default_questions();
}

bool QuizGame::load_from_file(const std::string& filename) {
    return questionBank.load_from_file(filename);
}

void QuizGame::run() {
    Gamemode mode = config.get_game_mode();

    switch (mode) {
        case Gamemode::Classic:
            GameModes::run_classic(*this);
            break;

        case Gamemode::QuickAttack:
            GameModes::run_quick_attack(*this);
            break;

        case Gamemode::Survival:
            GameModes::run_survival(*this);
            break;

        case Gamemode::Marathon:
            GameModes::run_marathon(*this);
            break;

        case Gamemode::Lightning:
            GameModes::run_lightning(*this);
            break;

        case Gamemode::Practice:
            GameModes::run_practice(*this);
            break;

        default:
            std::cout << ColorTheme::RED
                      << "⚠️  Unknown game mode! Defaulting to Classic."
                      << ColorTheme::RESET << std::endl;
            GameModes::run_classic(*this);
            break;
    }
}
