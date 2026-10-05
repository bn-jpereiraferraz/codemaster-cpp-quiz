#ifndef COMMONGAMELOOP_H
#define COMMONGAMELOOP_H

#include "core/IGameState.h"
#include "core/Gamemode.h"
#include "models/Question.h"

//==================
// COMMON GAME LOOP (Refactored)
//==================
// Orchestrates the main game loop
// Single Responsibility: Game Flow Orchestration
class CommonGameLoop {
public:
    // Run the common game loop for any mode
    static void run(IGameState& game);

private:
    // Setup phase
    static void setup_mode(IGameState& game);

    // Main question loop
    static void question_loop(IGameState& game);

    // Handle single question
    static void handle_question(IGameState& game, Question& q,
                              size_t questionNum, size_t totalQuestions);

    // Get user input with validation and lifeline handling
    static std::string get_user_answer(IGameState& game, Question& q, bool& skipped);

    // Process answer and update score
    static void process_answer(IGameState& game, const Question& q,
                              const std::string& answer);
};

#endif
