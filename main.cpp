#include <iostream>
#include "quiz.h"

int main()
{
    QuizGame game; //QuizGame Object

    bool fileLoaded = game.load_from_file("questions.txt"); //Load from file

    //if file loading failed use default questions
    if (!fileLoaded){
        std::cout << "Could not load questions from file." << std::endl;
        std::cout << "Loading default questions instead..." << std::endl;
        game.load_default_questions();
    }

    //run the game
    game.run();

    return 0;
}