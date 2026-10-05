#ifndef GAMEMODERUNNER_H
#define GAMEMODERUNNER_H

#include "core/IGameState.h"
#include "core/Gamemode.h"

class GameModeRunner {
public:
    // Single method to run any mode
    static void run(IGameState& game, Gamemode mode, bool showBanner = true);

private:
    static void show_banner(Gamemode mode);
    static void save_statistics(IGameState& game);
};

#endif
