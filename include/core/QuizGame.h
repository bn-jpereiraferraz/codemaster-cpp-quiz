#ifndef QUIZGAME_H
#define QUIZGAME_H

#include "models/Question.h"
#include "core/QuestionBank.h"
#include "core/GameSession.h"
#include "core/GameConfiguration.h"
#include "core/IGameState.h"
#include "systems/Lifelines.h"
#include "systems/GlobalTimer.h"
#include "systems/Lives.h"
#include "core/Gamemode.h"
#include "systems/statistics.h"
#include <string>

class QuizGame : public IGameState {

private:
    QuestionBank questionBank;
    GameSession session;
    GameConfiguration config;

    Lifelines lifelines;
    GlobalTimer globalTimer;
    Lives lives;
    Statistics stats;

public:
    QuizGame();
    ~QuizGame() override;

    // IGameState Interface Implementation
    QuestionBank& get_question_bank() override;
    const QuestionBank& get_question_bank() const override;
    GameSession& get_session() override;
    const GameSession& get_session() const override;
    GameConfiguration& get_configuration() override;
    const GameConfiguration& get_configuration() const override;
    Lifelines& get_lifelines() override;
    const Lifelines& get_lifelines() const override;
    Lives& get_lives() override;
    const Lives& get_lives() const override;
    GlobalTimer& get_global_timer() override;
    const GlobalTimer& get_global_timer() const override;
    Statistics& get_statistics() override;
    const Statistics& get_statistics() const override;

    // Question loading
    bool load_from_file(const std::string& filename);
    void load_default_questions();

    // Core game execution
    void run();
};

#endif
