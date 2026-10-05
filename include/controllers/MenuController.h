#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "core/Gamemode.h"
#include "core/IGameState.h"
#include <string>

class MenuController {
public:
    MenuController();

    void showMainMenu();
    void showGameModeMenu();
    void showStatisticsMenu(IGameState& game);
    void configureGame(IGameState& game);

    Gamemode selectGameMode();
    bool promptLoadSave(IGameState& game, const std::string& saveFilename);

private:
    void handleStatisticsMenuChoice(int choice, IGameState& game);

    void configureQuestionCount(IGameState& game);
    void configureDifficulty(IGameState& game);
    void configureCategory(IGameState& game);
    void configureTimer(IGameState& game);
    void configureLifelines(IGameState& game);
};

#endif
