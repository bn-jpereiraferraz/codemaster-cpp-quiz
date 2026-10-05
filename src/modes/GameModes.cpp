#include "modes/GameModes.h"
#include "core/GameModeRunner.h"

void GameModes::run_classic(IGameState& game) {
    GameModeRunner::run(game, Gamemode::Classic, true);  // true = show banner
}

void GameModes::run_quick_attack(IGameState& game) {
    GameModeRunner::run(game, Gamemode::QuickAttack, false);
}

void GameModes::run_survival(IGameState& game) {
    GameModeRunner::run(game, Gamemode::Survival, false);
}

void GameModes::run_marathon(IGameState& game) {
    GameModeRunner::run(game, Gamemode::Marathon, false);
}

void GameModes::run_lightning(IGameState& game) {
    GameModeRunner::run(game, Gamemode::Lightning, false);
}

void GameModes::run_practice(IGameState& game) {
    GameModeRunner::run(game, Gamemode::Practice, false);
}
