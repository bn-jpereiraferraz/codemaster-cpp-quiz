#include "ui/QuestionPresenter.h"
#include "ui/QuestionRenderer.h"
#include "ui/ColorTheme.h"
#include <iostream>

void QuestionPresenter::display_header(size_t currentQuestion, size_t totalQuestions) {
    std::cout << "\n\n\n";
    ColorTheme::print_question_header(currentQuestion, totalQuestions);
    ColorTheme::print_progress_bar(currentQuestion, totalQuestions);
}

void QuestionPresenter::display_question(const Question& question) {
    QuestionRenderer::display_boxed(question);
}

void QuestionPresenter::display_lifelines(const IGameState& game) {
    if (game.get_configuration().are_lifelines_enabled()) {
        game.get_lifelines().display_available();
    }
}

void QuestionPresenter::display_timer_warning(int seconds) {
    std::cout << ColorTheme::YELLOW << "\n⏱️  Timer: "
              << seconds << " seconds" << ColorTheme::RESET << std::endl;
}

void QuestionPresenter::display_hint(const std::string& hint) {
    std::cout << ColorTheme::YELLOW << "💡 Hint: " << hint
              << ColorTheme::RESET << std::endl;
}

void QuestionPresenter::display_correct_feedback(int points, int bonusPoints) {
    std::cout << ColorTheme::GREEN << "\n✓ Correct!" << ColorTheme::RESET;
    if (bonusPoints > 0) {
        std::cout << ColorTheme::YELLOW << " (+" << bonusPoints << " speed bonus)"
                  << ColorTheme::RESET;
    }
    std::cout << " +" << points << " points" << std::endl;
}

void QuestionPresenter::display_wrong_feedback() {
    std::cout << ColorTheme::RED << "\n✗ Wrong!" << ColorTheme::RESET << std::endl;
}

void QuestionPresenter::display_skip_notification() {
    std::cout << ColorTheme::YELLOW << "⏭️  Question skipped!"
              << ColorTheme::RESET << std::endl;
}

void QuestionPresenter::display_fifty_fifty_notification() {
    std::cout << ColorTheme::MAGENTA << "🎲 50/50 used! Two wrong answers removed."
              << ColorTheme::RESET << std::endl;
}
