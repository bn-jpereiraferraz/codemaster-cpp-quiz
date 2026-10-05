#include "controllers/ResultsManager.h"
#include "ui/ResultsDisplay.h"
#include "ui/AchievementDisplay.h"
#include "ui/ColorTheme.h"
#include "models/ResultsSummary.h"
#include "models/Achievement.h"
#include "processors/GradeCalculator.h"
#include "processors/AchievementChecker.h"
#include <iostream>

ResultsManager::ResultsManager() {
}

void ResultsManager::displayResults(IGameState& game) {
    size_t totalQuestions = game.get_question_bank().filtered_questions_count();

    if (totalQuestions == 0) {
        std::cout << ColorTheme::RED << "No questions were answered!"
                  << ColorTheme::RESET << std::endl;
        return;
    }

    ResultsSummary results = game.get_session().get_summary(totalQuestions);
    results.grade = GradeCalculator::calculate_grade(results.get_score_percentage());

    ResultsDisplay::show_results(results, game.get_configuration().get_game_mode());
}

void ResultsManager::displayAchievements(IGameState& game) {
    int questionsAnswered = game.get_session().get_current_question_index();

    if (questionsAnswered < 3) {
        std::cout << "\n" << ColorTheme::YELLOW
                  << "💪 Keep practicing! Try again to earn achievements!"
                  << ColorTheme::RESET << std::endl;
        return;
    }

    ResultsSummary results = game.get_session().get_summary(
        game.get_question_bank().filtered_questions_count());
    std::vector<Achievement> achievements = AchievementChecker::check_achievements(results);

    AchievementDisplay::show_unlocked_achievements(achievements);
}
