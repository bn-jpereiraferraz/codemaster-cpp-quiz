#ifndef GAMEMODES_H
#define GAMEMODES_H

#include "core/IGameState.h" 


//==================
//GAME MODES HANDLER
//==================
//Implements the 6 different gameplay modes for QuizGame

//Architecture Details:
//All Methods are static
//Friend of QuizGame (in order to access private members)
//Each mode takes QuizGame& reference to operate on

//Game Modes need deep access to QuizGame internals:
//-questions vector to iterate
//-earnedScore, correctCount (to update)
//globalTimer, lives(mode - specific objects)
//-Private helper Methods

class GameModes{
public:
    // All methods now use IGameState interface instead of QuizGame direct access
    static void run_classic(IGameState& game);
    static void run_quick_attack(IGameState& game);
    static void run_survival(IGameState& game);
    static void run_marathon(IGameState& game);
    static void run_lightning(IGameState& game);
    static void run_practice(IGameState& game);
};

#endif