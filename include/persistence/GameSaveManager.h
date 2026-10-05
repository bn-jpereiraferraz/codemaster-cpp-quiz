#ifndef GAMESAVEMANAGER_H
#define GAMESAVEMANAGER_H

#include "core/GameSession.h"
#include "core/GameConfiguration.h"
#include "systems/Lifelines.h"
#include <string>

class GameSaveManager {
public:
    GameSaveManager();

    bool save(const std::string& filename,
              const GameSession& session,
              const GameConfiguration& config,
              const Lifelines& lifelines);

    bool load(const std::string& filename,
              GameSession& session,
              GameConfiguration& config,
              Lifelines& lifelines);

    bool exists(const std::string& filename) const;
    void deleteSave(const std::string& filename);

private:
    void writeHeader(std::ofstream& file) const;
    void writeSessionData(std::ofstream& file, const GameSession& session) const;
    void writeConfigData(std::ofstream& file, const GameConfiguration& config) const;
    void writeLifelineData(std::ofstream& file, const Lifelines& lifelines) const;

    void parseKeyValue(const std::string& key, const std::string& value,
                       GameSession& session, GameConfiguration& config, Lifelines& lifelines);
};

#endif
