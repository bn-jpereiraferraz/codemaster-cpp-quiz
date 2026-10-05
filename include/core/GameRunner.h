#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "core/QuizGame.h"
#include "controllers/MenuController.h"
#include "controllers/ResultsManager.h"
#include "persistence/GameSaveManager.h"

class GameRunner {
private:
    QuizGame game;
    MenuController menuController;
    ResultsManager resultsManager;
    GameSaveManager saveManager;
    bool running;

public:
    GameRunner();

    void run();

private:
    void handle_main_menu();
    void handle_new_quiz();
    void handle_configure_settings();
    void handle_view_statistics();
    void handle_exit();
};

#endif
