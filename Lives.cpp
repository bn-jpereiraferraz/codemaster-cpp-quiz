#include "Lives.h"
#include "ColorTheme.h"
#include <iostream>


//============
//CONSTRUCTOR
//============
//initialize with specified number of lives
//Parameters: 
//lives - Starting life count(default: 3)
Lives::Lives(int lives)
    :totalLives(lives), currentLives(lives){
        //Start at full health
    }

//============
//LOSE LIFE
//============
//Deduct one life (called on wrong answer)
//Note: Lives cannot go below zero
void Lives::lose_life(){
    if (currentLives > 0){
        currentLives--;
    }
}

//=======
//RESET
//=======
//Restore Lives to starting amount
void Lives::reset(){
    currentLives = totalLives;
}

//=============
//GET REMAINING
//=============
//return current number of lives left
int Lives::get_remaining()const{
    return currentLives;
}

//===========
//GET TOTAL
//===========
//Return maximum life capacity
int Lives::get_total()const{
    return totalLives;
}

//============
//IS GAME OVER
//============
//Check if player has run out of lives
//Returns: true if 0 lives, false otherwise
bool Lives::is_game_over()const{
    return currentLives <= 0;
}

//===========
//DISPLAY
//===========
//Print visual representation of lives
void Lives::display()const{
    std::cout << ColorTheme::YELLOW << "Lives: ";

    //Print Filles hearts for remaining Lives
    for (int i  = 0; i < currentLives; i++)
    {
        std::cout << ColorTheme::RED << "❤️ ";
    }

    //Print empty hearts for lost lives
    for(int i = currentLives; i < totalLives; i++)
    {
        std::cout << ColorTheme::DIM << "♡ ";
    }

    std::cout << ColorTheme::RESET << std::endl;
}

//==================
//GET HEARTS STRING
//==================
//Return hearts as a string (for inline display)
//RETURNS: String like "❤️❤️♡" (2/3 lives)
std::string Lives::get_hearts_string()const{
    std::string hearts = "";

    //Add filled hearts
    for(int i = 0; i < currentLives; i++)
    {
        hearts += "❤️";
    }

    //Add empty hearts
    for (int i = currentLives; i < totalLives; i++)
    {
        hearts += "♡";
    }
    return hearts;
}

//==============
//SET LIVES
//==============
//Manually set current life count(used when loading saves)
//Parameters: 
//lives - New life count to set
void Lives::set_lives(int lives){
    currentLives = lives;
    if (currentLives < 0) currentLives = 0;
    if (currentLives > totalLives) currentLives = totalLives;
}
