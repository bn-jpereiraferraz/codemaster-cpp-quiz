#ifndef QUIZGAME_H
#define QUIZGAME_H

#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "TrueFalseQuestion.h"
#include "Lifelines.h"
#include "GlobalTimer.h"
#include "Lives.h"
#include <string>
#include <vector>

//==================
// DIFFICULTY ENUM
//==================
// Matches point values in questions.txt for filtering
enum Difficulty {
    EASY = 5,      // 5-point questions
    MEDIUM = 10,   // 10-point questions
    HARD = 15,     // 15-point questions
    MIXED = 0      // All difficulties (no filter)
};

//==============
//GAME MODE ENUM
//==============
//Different gameplay modes with unique rules

enum Gamemode{
    CLASSIC, //Normal mode configurable (current gameplay)
    QUICK_ATTACK, //5min timelimit, wrong answer = -15s penalty
    SURVIVAL, //3 lives, lose 1 per answer
    MARATHON, //All 300 questions, track total time
    LIGHTNING, //10 seconds per questions (strict)
    PRACTICE //No pressure, see correct answers
};

//==================
// GAME MANAGER - Main quiz controller
//==================
class QuizGame {
    //=== FRIEND CLASSES ===
    //GameModes needs access to private members
    //(questions, scores, timers, lifelines, helper methods, etc.)
    friend class GameModes;
 

private:
    //=== HELPER METHODS ===
    Question* parse_question_line(std::string line);  // Parse file format
    void display_live_stats(int current, int total);  // Stats every 5 questions
    void shuffle_questions();                         // Randomize order
    int calculate_bonus_points(int basePoints, int secondsUsed, int timeLimit);  // Speed bonus
    void filter_by_difficulty(Difficulty diff);       // Keep only matching difficulty
    void apply_fifty_fifty(MultipleChoiceQuestion* mcq);  // Remove 2 wrong answers

    //=== QUESTIONS ===
    std::vector<Question*> questions;         // All loaded questions
    std::vector<Question*> filteredQuestions; // After difficulty filter
    int currentQuestionIndex;                 // Current position (for resume)

    //=== SCORING ===
    int totalScore;        // Total possible points
    int earnedScore;       // Points earned
    int correctCount;      // Questions answered correctly
    int currentStreak;     // Consecutive correct (resets on wrong)
    int bestStreak;        // Highest streak this session
    int totalBonusPoints;  // Speed bonus points

    //=== SETTINGS ===
    int totalQuestionsToAsk;      // How many to ask (50-300)
    Difficulty selectedDifficulty; // Which difficulty
    bool timerEnabled;            // Timer on/off
    int questionTimeLimit;        // Seconds per question
    bool lifelinesEnabled;        // Lifelines on/off
    Gamemode currentGameMode;     //Current Game Mode

    //=== GAME OBJECTS ===
    Lifelines lifelines;

    //=== GAME MODE OBJECTS ===
    GlobalTimer globalTimer; //Quick Attack  - 5 min count down
    Lives lives; //Survival mode 3 lives game over at 0;

public:
    //=== SETUP ===
    QuizGame();   // Initialize defaults
    ~QuizGame();  // Clean up allocated questions

    //=== QUESTION LOADING ===
    void add_question(Question* q);           // Add single question
    void load_default_questions();            // Load 4 fallback questions
    bool load_from_file(std::string filename); // Load from file (true if success)

    //=== GAME FLOW ===
    void run();                   // Main game loop
    void display_results();       // Final score and grade
    void display_achievements();  // Badges earned

    //=== MENU & CONFIG ===
    void show_main_menu();     // Display main menu
    void show_game_mode_menu(); //Display game mode selection
    void configure_game();     // Interactive settings
    bool prompt_load_save();   // Ask to continue saved game (true if loaded)

    //=== SAVE/LOAD ===
    bool save_game(std::string filename);  // Save state (true if success)
    bool load_game(std::string filename);  // Load state (true if success)
    bool has_saved_game() const;           // Check if save exists
    void delete_save();                    // Remove save file

    //=== SETTINGS ===
    void set_question_count(int count);           // Set how many questions
    void set_difficulty(Difficulty diff);         // Set difficulty filter
    void enable_timer(int secondsPerQuestion);    // Turn on timer
    void disable_timer();                         // Turn off timer
    void enable_lifelines();                      // Turn on lifelines
    void disable_lifelines();                     // Turn off lifelines
    void set_game_mode(Gamemode mode);            //Set game mode
};

#endif
