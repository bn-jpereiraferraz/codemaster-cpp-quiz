#include "core/CommonGameLoop.h"
#include "core/Constants.h"
#include "modes/ModeSetup.h"
#include "ui/QuestionPresenter.h"
#include "ui/ColorTheme.h"
#include "utils/AnswerValidator.h"
#include "systems/LifelineHandler.h"
#include "systems/Timer.h"
#include <iostream>

void CommonGameLoop::run(IGameState& game) {
    setup_mode(game);
    question_loop(game);
    // Results are displayed by ResultsManager after this returns
}

void CommonGameLoop::setup_mode(IGameState& game) {
    // Mode comes from game.get_configuration().get_game_mode()

    if (!game.get_question_bank().has_questions()) {
        std::cerr << ColorTheme::RED << "Error: No questions loaded!"
                  << ColorTheme::RESET << std::endl;
        return;
    }

    // Apply filters and shuffle
    game.get_question_bank().filter_by_difficulty(game.get_configuration().get_difficulty());
    game.get_question_bank().filter_by_category(game.get_configuration().get_category());
    game.get_question_bank().shuffle_questions();

    // Limit to question count
    int userQuestionCount = game.get_configuration().get_question_count();
    if (game.get_question_bank().filtered_questions_count() > static_cast<size_t>(userQuestionCount)) {
        game.get_question_bank().limit_to_count(userQuestionCount);
    }

    // Calculate and set total score
    int totalScore = game.get_question_bank().calculate_total_score();
    game.get_session().set_total_score(totalScore);

    // Display configuration
    std::cout << ColorTheme::YELLOW << "\n🎯 Quiz configured:" << ColorTheme::RESET << std::endl;
    std::cout << "   Questions: " << ColorTheme::BOLD
              << game.get_question_bank().filtered_questions_count()
              << ColorTheme::RESET << std::endl;
    std::cout << "   Total Points: " << ColorTheme::BOLD
              << game.get_session().get_total_score()
              << ColorTheme::RESET << std::endl;

    if (game.get_configuration().is_timer_enabled()) {
        std::cout << "   Timer: " << ColorTheme::RED
                  << game.get_configuration().get_timer_seconds()
                  << " seconds per question" << ColorTheme::RESET << std::endl;
    }

    if (game.get_configuration().are_lifelines_enabled()) {
        std::cout << "   Lifelines: " << ColorTheme::GREEN << "Enabled 💡"
                  << ColorTheme::RESET << std::endl;
    }

    std::cout << "\n" << ColorTheme::DIM << "Press Enter to begin..."
              << ColorTheme::RESET;
    std::cin.get();
}

void CommonGameLoop::question_loop(IGameState& game) {
    const std::vector<Question*>& questions = game.get_question_bank().get_filtered_questions();

    for (size_t i = game.get_session().get_current_question_index(); i < questions.size(); i++) {
        game.get_session().set_current_question_index(i);
        Question* q = questions[i];

        if (q) {
            handle_question(game, *q, i + 1, questions.size());
        }
    }
}

void CommonGameLoop::handle_question(IGameState& game, Question& q,
                                     size_t questionNum, size_t totalQuestions) {
    // Display question
    QuestionPresenter::display_header(questionNum, totalQuestions);
    QuestionPresenter::display_lifelines(game);
    std::cout << "\n";
    QuestionPresenter::display_question(q);

    // Reset hint level
    game.get_session().reset_hint_level();

    // Start timer
    Timer questionTimer(game.get_configuration().get_timer_seconds());
    if (game.get_configuration().is_timer_enabled()) {
        questionTimer.start();
        QuestionPresenter::display_timer_warning(game.get_configuration().get_timer_seconds());
    }

    // Get answer
    bool skipped = false;
    std::string answer = get_user_answer(game, q, skipped);

    // Stop timer
    if (game.get_configuration().is_timer_enabled()) {
        questionTimer.stop();
    }

    // Process answer (if not skipped)
    if (!skipped) {
        process_answer(game, q, answer);
    }

    // Advance to next question
    game.get_session().advance_question();
}

std::string CommonGameLoop::get_user_answer(IGameState& game, Question& q, bool& skipped) {
    skipped = false;
    std::string answer;

    while (true) {
        std::cout << ColorTheme::CYAN << "\nYour answer";

        if (LifelineHandler::are_lifelines_enabled(game)) {
            std::cout << ColorTheme::DIM << " (or 'hint'";
            if (game.get_lifelines().can_use_fifty_fifty() && q.get_type() == GameConstants::QUESTION_TYPE_MULTIPLE_CHOICE) {
                std::cout << ", '5050'";
            }
            if (game.get_lifelines().can_use_skip()) {
                std::cout << ", 'skip'";
            }
            std::cout << ")" << ColorTheme::RESET;
        }

        std::cout << ": ";
        std::getline(std::cin, answer);

        // Check for special commands
        auto command = AnswerValidator::parse_special_command(answer);

        switch (command) {
            case AnswerValidator::SpecialCommand::Hint:
                LifelineHandler::use_hint(game, q);
                continue;

            case AnswerValidator::SpecialCommand::Skip:
                if (LifelineHandler::use_skip(game)) {
                    skipped = true;
                    return "";
                }
                continue;

            case AnswerValidator::SpecialCommand::FiftyFifty:
                if (LifelineHandler::use_fifty_fifty(game, q)) {
                    // Redisplay question with removed options
                    QuestionPresenter::display_question(q);
                }
                continue;

            case AnswerValidator::SpecialCommand::None:
                // Validate answer format
                if (AnswerValidator::is_valid(q, answer)) {
                    return answer;
                } else {
                    std::cout << ColorTheme::RED
                              << AnswerValidator::get_error_message(q)
                              << ColorTheme::RESET << std::endl;
                    continue;
                }
        }
    }
}

void CommonGameLoop::process_answer(IGameState& game, const Question& q,
                                    const std::string& answer) {
    bool correct = q.check_answer(answer);

    if (correct) {
        int points = q.get_points();
        int bonusPoints = 0;  // No time bonus currently implemented

        game.get_session().record_correct_answer(points, bonusPoints);
        QuestionPresenter::display_correct_feedback(points, bonusPoints);
    } else {
        game.get_session().record_wrong_answer();
        QuestionPresenter::display_wrong_feedback();
    }
}
