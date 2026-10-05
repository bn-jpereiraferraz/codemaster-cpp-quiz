#ifndef ISCORETRACKER_H
#define ISCORETRACKER_H

#include "core/GameSession.h"

//==================
// SCORE TRACKER INTERFACE
//==================
// Focused interface for score and session tracking
// Single Responsibility: Score management
class IScoreTracker {
public:
    virtual ~IScoreTracker() = default;

    virtual GameSession& get_session() = 0;
    virtual const GameSession& get_session() const = 0;
};

#endif
