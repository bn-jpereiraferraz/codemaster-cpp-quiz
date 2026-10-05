#include "systems/LifelineHandler.h"
#include "ui/QuestionPresenter.h"
#include "ui/ColorTheme.h"
#include "core/Constants.h"
#include <iostream>

bool LifelineHandler::use_hint(IGameState& game, const Question& question) {
    game.get_session().increment_hint_level();
    std::string hint = question.get_hint(game.get_session().get_hint_level());
    QuestionPresenter::display_hint(hint);
    return true;
}

bool LifelineHandler::use_skip(IGameState& game) {
    if (!are_lifelines_enabled(game)) {
        return false;
    }

    if (game.get_lifelines().can_use_skip()) {
        game.get_lifelines().use_skip();
        QuestionPresenter::display_skip_notification();
        return true;
    } else {
        std::cout << ColorTheme::RED << "❌ Skip already used!"
                  << ColorTheme::RESET << std::endl;
        return false;
    }
}

bool LifelineHandler::use_fifty_fifty(IGameState& game, const Question& question) {
    if (!are_lifelines_enabled(game)) {
        return false;
    }

    // Only works for multiple choice
    if (question.get_type() != GameConstants::QUESTION_TYPE_MULTIPLE_CHOICE) {
        std::cout << ColorTheme::RED << "❌ 50/50 only works for multiple choice questions!"
                  << ColorTheme::RESET << std::endl;
        return false;
    }

    if (game.get_lifelines().can_use_fifty_fifty()) {
        game.get_lifelines().use_fifty_fifty();
        QuestionPresenter::display_fifty_fifty_notification();
        // Note: Actual removal of options would need to be handled by caller
        return true;
    } else {
        std::cout << ColorTheme::RED << "❌ 50/50 already used!"
                  << ColorTheme::RESET << std::endl;
        return false;
    }
}

bool LifelineHandler::are_lifelines_enabled(const IGameState& game) {
    return game.get_configuration().are_lifelines_enabled();
}
