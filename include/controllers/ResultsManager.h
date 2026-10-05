#ifndef RESULTSMANAGER_H
#define RESULTSMANAGER_H

#include "core/IGameState.h"

class ResultsManager {
public:
    ResultsManager();

    void displayResults(IGameState& game);
    void displayAchievements(IGameState& game);
};

#endif
