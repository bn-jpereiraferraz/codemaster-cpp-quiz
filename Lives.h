#ifndef LIVES_H
#define LIVES_H
#include <string>

//==================================
//LIVES SYSTEM - For Survival Mode
//==================================
//Tracks Player lives in survival mode
//Each wrong answer costs one life

//Key Features: 
//-Starts with N lives (default 3)
//-Lose one life per wrong answer
//-Visual display with heart symbols (❤️❤️❤️)
//-Game Over detection (0 Lives remaining)
//Save/Load support for resume feature

//Usage:
//Lives lives(3);

//lives.lose_life(); //Wrong answer
//lives.display(); //Show ❤️❤️♡ (2 Lives left)

//if (lives.is_game_over()){
// No Lives remaining}
//====================================

class Lives{

    private: 
        int totalLives; //maximum Lives (Starting Amount)
        int currentLives; //Current remaining Lives
    
    public:

        //Contructor
        Lives(int lives = 3); //Default 3 Lives

        //=== LIFE MANAGEMENT ===
        void lose_life(); //Deduct one life
        void reset(); //restore to full lives

        //=== QUERIES ===
        int get_remaining()const; //How many Lives left
        int get_total()const; //Maximum Lives
        bool is_game_over()const; //Are all lives gone

        //=== Display ===
        void display()const; //print visual hearts here(❤️❤️❤️)
        std::string get_hearts_string()const; //Get hearts as a string

        //=== SAVE/LOAD ===
        void set_lives(int lives); //Set current lives for loading saves
};

#endif LIVES_H