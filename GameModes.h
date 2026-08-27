#ifndef GAMEMODES_H
#define GAMEMODES_H

//Forward declaration - tells compiler QuizGame exists
//We don't need full definition, just the name;
class QuizGame; 


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

    //=== MODE IMPLEMENTATIONS ===
    //Each methods implements one complete game mode
    //Parameter: QuizGame& game - reference to the game instance
public:
    static void run_classic(QuizGame& game); //Classic: configurable gameplay
    static void run_quick_attack(QuizGame& game); //Quick Attack
    static void run_survival(QuizGame& game); //Survival 3 lives
    static void run_marathon(QuizGame& game); //Marathon: all questions
    static void run_lightning(QuizGame& game); //Lightning round
    static void run_practice(QuizGame& game); //Practice: no pressure
};

#endif