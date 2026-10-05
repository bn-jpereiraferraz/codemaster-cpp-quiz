#ifndef LIFELINEHANDLER_H
#define LIFELINEHANDLER_H

#include "core/IGameState.h"
#include "models/Question.h"

//==================
// LIFELINE HANDLER
//==================
// Processes lifeline commands (hint, skip, 50/50)
// Single Responsibility: Lifeline Management
class LifelineHandler {
public:
    // Process hint request
    static bool use_hint(IGameState& game, const Question& question);

    // Process skip request
    static bool use_skip(IGameState& game);

    // Process 50/50 request (only for multiple choice)
    static bool use_fifty_fifty(IGameState& game, const Question& question);

    // Check if lifelines are enabled
    static bool are_lifelines_enabled(const IGameState& game);
};

#endif
