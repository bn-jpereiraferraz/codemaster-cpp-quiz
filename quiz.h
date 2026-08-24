#ifndef _QUIZ_H_
#define _QUIZ_H_

#include <string>
#include <vector>
#include <chrono>  // Time measurement for countdown timers
#include <random>  // Question shuffling


//==================
// DIFFICULTY ENUM
//==================
// Matches point values in questions.txt for filtering
enum Difficulty{
    EASY = 5,      // 5-point questions
    MEDIUM = 10,   // 10-point questions
    HARD = 15,     // 15-point questions
    MIXED = 0      // All difficulties (no filter)
};


//==================
// BASE CLASS - Abstract Question
//==================
class Question{
protected:
    std::string questionText;
    int points;

public:
    Question(std::string text, int pts);
    virtual ~Question();  // Virtual for proper inheritance cleanup

    // Pure virtual - children must implement
    virtual void display() = 0;
    virtual bool checkAnswer(std::string answer) = 0;

    int get_points();
};


//==================
// CHILD CLASS - Multiple Choice (4 options)
//==================
class MultipleChoiceQuestion: public Question{
private:
    std::vector<std::string> options;  // A, B, C, D options
    char correctAnswer;                 // Correct option letter

public:
    MultipleChoiceQuestion(std::string text, int pts, std::vector<std::string> opts, char correct);
    ~MultipleChoiceQuestion();

    void display() override;
    bool checkAnswer(std::string answer) override;
    std::vector<std::string>get_options()const {return options;}
    char get_correct_answer()const{return correctAnswer;}
};


//==================
// CHILD CLASS - True/False
//==================
class TrueFalseQuestion: public Question{
private:
    bool correctAnswer;

public:
    TrueFalseQuestion(std::string text, int pts, bool correct);
    ~TrueFalseQuestion();

    void display() override;
    bool checkAnswer(std::string answer) override;
};


//==================
// COLOR THEME - ANSI terminal styling
//==================
class ColorTheme{
public:
    // ANSI color codes (static = shared across instances)
    static const char* RESET;
    static const char* RED;
    static const char* GREEN;
    static const char* YELLOW;
    static const char* BLUE;
    static const char* MAGENTA;
    static const char* CYAN;
    static const char* BOLD;
    static const char* DIM;

    // Visual output methods
    static void print_banner();
    static void print_separator();
    static void print_correct_message(int points);
    static void print_wrong_message();
    static void print_question_header(int current, int total);
    static void print_progress_bar(int current, int total);
};


//==================
// TIMER - Countdown for each question
//==================
class Timer{
private:
    int timeLimit;  // Seconds allowed
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    bool running;

public:
    Timer(int seconds);  // Initialize with time limit

    void start();  // Begin countdown
    void stop();   // End countdown

    int get_elapsed_seconds() const;   // Time used so far
    int get_remaining_seconds() const; // Time left
    bool is_time_up() const;           // Check if expired
    bool is_running() const;           // Check if active
};


//==================
// LIFELINES - Game show style helps
//==================
// Each can only be used ONCE per game
class Lifelines{
private:
    bool fiftyFiftyAvailable;  // Remove 2 wrong answers (MC only)
    bool skipAvailable;        // Skip question (no penalty)
    bool hintAvailable;        // Show hint (future feature)

public:
    Lifelines();

    // Check availability
    bool can_use_fifty_fifty() const;
    bool can_use_skip() const;
    bool can_use_hint() const;

    // Consume lifeline (returns false if already used)
    bool use_fifty_fifty();
    bool use_skip();
    bool use_hint();

    void display_available() const;  // Show available helps
    void reset();                    // Make all available again

    // Save/Load state
    bool is_fifty_fifty_used() const;
    bool is_skip_used() const;
    bool is_hint_used() const;

    void set_fifty_fifty_used(bool used);
    void set_skip_used(bool used);
    void set_hint_used(bool used);
};


//==================
// GAME MANAGER - Main quiz controller
//==================
class QuizGame{
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

    //=== GAME OBJECTS ===
    Lifelines lifelines;

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
};

#endif
