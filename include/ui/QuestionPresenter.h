#ifndef QUESTIONPRESENTER_H
#define QUESTIONPRESENTER_H

#include "core/IGameState.h"
#include "models/Question.h"
#include <cstddef>

//==================
// QUESTION PRESENTER
//==================
// Handles displaying questions and related UI elements
// Single Responsibility: Question Display
class QuestionPresenter {
public:
    // Display question header and progress
    static void display_header(size_t currentQuestion, size_t totalQuestions);

    // Display the question itself
    static void display_question(const Question& question);

    // Display lifelines status
    static void display_lifelines(const IGameState& game);

    // Display timer warning
    static void display_timer_warning(int seconds);

    // Display hint
    static void display_hint(const std::string& hint);

    // Display feedback for correct/wrong answer
    static void display_correct_feedback(int points, int bonusPoints = 0);
    static void display_wrong_feedback();

    // Display skip notification
    static void display_skip_notification();

    // Display 50/50 notification
    static void display_fifty_fifty_notification();
};

#endif
