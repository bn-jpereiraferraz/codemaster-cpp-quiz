#include "core/GameModeRunner.h"
#include "core/CommonGameLoop.h"
#include "core/Constants.h"
#include "ui/AsciiArt.h"

void GameModeRunner::run(IGameState& game, Gamemode mode, bool showBanner) {
    if (showBanner) {
        show_banner(mode);
    }

    (void)mode;  // Parameter kept for API compatibility, but mode is in game config
    CommonGameLoop::run(game);
    save_statistics(game);
}

void GameModeRunner::show_banner(Gamemode mode) {
    switch (mode) {
        case Gamemode::Classic:
            AsciiArt::display_classic_banner();
            break;
        // Add other mode banners if they exist
        default:
            break;
    }
}

void GameModeRunner::save_statistics(IGameState& game) {
    game.get_statistics().record_game(
        game.get_configuration().get_game_mode(),
        game.get_session().get_earned_score(),
        game.get_session().get_correct_count(),
        game.get_question_bank().filtered_questions_count(),
        game.get_session().get_best_streak()
    );
    game.get_statistics().save_to_file(GameConstants::STATISTICS_FILE);
}
