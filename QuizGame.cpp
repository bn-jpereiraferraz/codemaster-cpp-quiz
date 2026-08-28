#include "QuizGame.h"
#include "GameModes.h"
#include "ColorTheme.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <cctype>

//GAME MANAGER CLASS: QuizGame
//============================

//Constructor - initializes the game with 0 points
QuizGame::QuizGame()
    :totalScore(0), 
     earnedScore(0), 
     correctCount(0), 
     currentStreak(0), 
     bestStreak(0),
     totalBonusPoints(0),               //Initialize bonus points
     currentQuestionIndex(0),           //Start at first question
     totalQuestionsToAsk(300),          //Default to all questions
     selectedDifficulty(MIXED),         //Default to all difficulties
     timerEnabled(false),               //Timer off by default
     questionTimeLimit(30),             //Default 30 seconds
     lifelinesEnabled(false),            //Lifelines off by default
     currentGameMode(CLASSIC),           //Default Classic Mode
     globalTimer(300),                   //5 minutes for Quickattack
     lives(3)                            //3 lives for survival 
    {
        //Initializer list sets both scores to 0
        //The questions vector is automatically initialized(empty)
        //No code needed in the body - initializer list did everything
    }

//Destructor - Critical for Memory Management
QuizGame::~QuizGame(){
    //We used 'new' to create Question objects, so we MUST 'delete' them
    //this prevents memory leaks;

    //Range based for loop: iterates through all question pointers

    for (Question* q : questions){
        delete q; //Calls virtual destructor chain;
                 //1- calls child destructor (MultipleChoice or TrueFalse)
                 //2- Then calls base Question destructor
                 //This is why virtual destructor is crucial
    }
    questions.clear(); //Empty the Vector;
}


//Add as question to the quiz
void QuizGame::add_question(Question* q){
    //Simply push the question pointer to our vector
    //The vector stores pointers, Not copies of the objects
    //This allows Polymorphism - we can store different question types;
    questions.push_back(q);
}

//Load some default hardcoded questions(fallback if file loading fails)
void QuizGame::load_default_questions(){
    //Using 'new' creates objects on the HEAP(dynami memory)
    //Returns a pointer to that object
    //These objects live until we explicitly 'delete' them
    //Question 1
    add_question(new MultipleChoiceQuestion("What does OOP stand for?",
    10, //Points for this question
    {"Object-Oriented-Programming", "Only One Person", 
    "Out Of Pizza", "Optimize Our Programs"}, 'A'));

    //Question 2
    add_question(new MultipleChoiceQuestion(
        "Which keyword is used for inheritance in C++?", 10,
        {"extends", "inherits", "public", "derive"},
        'C'));

    //Question 3
    add_question(new TrueFalseQuestion(
        "Pure virtual Methods are declared with = 0.", 10, true));

    //Question 4
    add_question(new TrueFalseQuestion(
        "You can create objects of abstract classes.", 10, false));
}


//===============
// MAIN GAME LOOP
//===============
void QuizGame::run() {
    // Dispatch based on selected game mode
    switch (currentGameMode) {
        case CLASSIC:
            GameModes::run_classic(*this);  // Pass *this = reference to current game
            break;

        case QUICK_ATTACK:
            GameModes::run_quick_attack(*this);
            break;

        case SURVIVAL:
            GameModes::run_survival(*this);
            break;

        case MARATHON:
            GameModes::run_marathon(*this);
            break;

        case LIGHTNING:
            GameModes::run_lightning(*this);
            break;

        case PRACTICE:
            GameModes::run_practice(*this);
            break;

        default:
            // Fallback to classic if unknown mode
            std::cout << ColorTheme::RED
                      << "⚠️  Unknown game mode! Defaulting to Classic."
                      << ColorTheme::RESET << std::endl;
            GameModes::run_lightning(*this);
            break;
    }
}
    


//Display final quiz results with grade
void QuizGame::display_results(){

    std::cout << "\n";
    ColorTheme::print_separator();
    ColorTheme::print_separator();

    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n            🎊 QUIZ COMPLETE! 🎊\n" << ColorTheme::RESET << std::endl;

    ColorTheme::print_separator();

    //Show final score with colors
    std::cout << ColorTheme::BOLD << "Final Score: " << ColorTheme::YELLOW;
    std::cout << earnedScore << " / " << totalScore << ColorTheme::RESET << std::endl;

    //Edge case: no questions were answered
    if (totalScore == 0){
        std::cout << ColorTheme::RED << "No questions were answered!" << ColorTheme::RESET << std::endl;
        return;
    }

    //Calculate percentage
    double percentage = (double)earnedScore / totalScore * 100;
    std::cout << ColorTheme::BOLD << "Percentage: " << ColorTheme::CYAN;
    std::cout.precision(1);
    std::cout << std::fixed << percentage << "%" << ColorTheme::RESET << std::endl;

    //Show Correct Count
    std::cout << ColorTheme::BOLD << "Correct Answers: " << ColorTheme::GREEN;
    std::cout << correctCount << " / " << filteredQuestions.size() << ColorTheme::RESET << std::endl;

    //Show best streak
    std::cout << ColorTheme::BOLD << "Best Streak: " << ColorTheme::MAGENTA;
    std::cout << bestStreak << ColorTheme::RESET << std::endl << std::endl;

    //Grade Calculation with colors
    std::cout << ColorTheme::BOLD << "Grade: ";
    if (percentage >= 80){
        std::cout << ColorTheme::GREEN << "A - Excellent! 🌟" << ColorTheme::RESET << std::endl;
    }
    else if(percentage >= 60){
        std::cout << ColorTheme::CYAN << "B - Good Job! 👍" << ColorTheme::RESET << std::endl;
    }
    else if(percentage >= 40){
        std::cout << ColorTheme::YELLOW << "C - Keep practicing! 📚" << ColorTheme::RESET << std::endl;
    }
    else{
        std::cout << ColorTheme::RED << "D - Review your Materials! 📖" << ColorTheme::RESET << std::endl;
    }

    ColorTheme::print_separator();
}

//Display live stats during the quiz - show current performance
void QuizGame::display_live_stats(int current, int /* total */){
    ColorTheme::print_separator();

    //calculate accuracy percentage
    double accuracy = 0.0;
    if (current > 0){
        accuracy = (double)correctCount / current * 100.0;
    }

    //Display stats in a box
    std::cout << ColorTheme::CYAN << "┌─────────────────────────────────────────┐" << std::endl;
    std::cout << "| " << ColorTheme::BOLD << "STATS" << ColorTheme::RESET << ColorTheme::CYAN;
    std::cout << "                                 |" << std::endl;
    std::cout << "├─────────────────────────────────────────┤" << std::endl;

    //Score
    std::cout << "| Score: " << ColorTheme::YELLOW << earnedScore << " / " << totalScore;
    std::cout << ColorTheme::CYAN;
    
    //Padding to align
    int padding = 29 - std::to_string(earnedScore).length() - std::to_string(totalScore).length();
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    //Accuracy
    std::cout << "| Accuracy: " << ColorTheme::GREEN;
    std::cout.precision(1);
    std::cout << std::fixed << accuracy << "%";
    std::cout << ColorTheme::CYAN;
    padding = 26 - 4; //Adjust for percentage display
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    //Current streak
    std::cout << "| Current Streak: " << ColorTheme::MAGENTA << currentStreak;
    std::cout << ColorTheme::CYAN;
    padding = 22 - std::to_string(currentStreak).length();
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;

    //Best streak
    std::cout << "| Best Streak: " << ColorTheme::MAGENTA << bestStreak;
    std::cout << ColorTheme::CYAN;
    padding = 25 - std::to_string(bestStreak).length();
    for (int i = 0; i < padding; i++) {
        std::cout << " ";
    }
    std::cout << "|" << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << ColorTheme::RESET << std::endl;

    ColorTheme::print_separator();
}

//Display Achievements and badges based on performance
void QuizGame::display_achievements(){
    // Calculate how many questions were actually answered
    int questionsAnswered = currentQuestionIndex;  // This tracks actual progress

    // Don't show achievements if barely any questions were answered
    if (questionsAnswered < 3) {
        std::cout << "\n" << ColorTheme::YELLOW
                  << "💪 Keep practicing! Try again to earn achievements!"
                  << ColorTheme::RESET << std::endl;
        return;
    }

    std::cout << "\n" << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << "🏆 ACHIEVEMENTS: " << ColorTheme::RESET << std::endl;

    //Perfect Score (only if answered at least 5 questions)
    if (earnedScore == totalScore && questionsAnswered >= 5){
        std::cout << ColorTheme::GREEN << " ⭐ PERFECT SCORE - Flawless Victory!" << ColorTheme::RESET << std::endl;
    }

    //high Streak achievements
    if (bestStreak >= 10){
        std::cout << ColorTheme::MAGENTA << " 🔥 ON FIRE - 10+ Question Streak!" << ColorTheme::RESET << std::endl;
    }else if (bestStreak >= 5) {
        std::cout << ColorTheme::CYAN << " ⚡ HOT STREAK - 5+ Questions in a row!" << ColorTheme::RESET << std::endl;
    }

    //Accuracy Achievements (based on questions actually answered, not all 300!)
    if (questionsAnswered > 0) {
        double accuracy = (double)correctCount / questionsAnswered * 100.0;
        if (accuracy >= 90.0) {
            std::cout << ColorTheme::GREEN << " 🎯 SHARPSHOOTER - 90%+ Accuracy!" << ColorTheme::RESET << std::endl;
        } else if (accuracy >= 75.0) {
            std::cout << ColorTheme::BLUE << " 📚 SCHOLAR - 75%+ Accuracy!" << ColorTheme::RESET << std::endl;
        }
    }

    //Completion Achievement (show actual number answered, not total loaded!)
    std::cout << ColorTheme::CYAN << " ✅ QUESTIONS ANSWERED: " << questionsAnswered << ColorTheme::RESET << std::endl;
}

//Helper function - converts one line from the quesitons file into a Question object
//This is PRIVATE - only QuizGame uses it
Question* QuizGame::parse_question_line(std::string line){
    //MC |Multiplechoice
    //TF | True or False

    //Skip empty lines and comment lines(startign with #)
    if (line.empty() || line[0] == '#'){
        return nullptr; //No valid question
    }

    //Find the first pipe '|' to extract question type
    //find () returns position of character,or npos if not found
    size_t firstPipe = line.find('|');
    if (firstPipe == std::string::npos) return nullptr; //in case of invalid format

    //Extract type (everything before first|)
    //substr(start, length) - extracts substring
    std::string type = line.substr(0, firstPipe);

    //Parse multiple Choice questions
    if (type == "MC"){
        //Example: MC | What is X?|10| o1,o2,o3,o4 | A
        //              ^          ^  ^             ^
        //            firstPipe   po2 pos4         pos6

        //Extract question text(between 1st and 2nd Pipe)
        size_t pos1 = firstPipe + 1; //Start after first'|'
        size_t pos2 = line.find('|', pos1); //Find next
        std::string questionText = line.substr(pos1, pos2 - pos1);

        //Extract points (between 2 and 3 Pipe)
        size_t pos3 = pos2 + 1;
        size_t pos4 = line.find('|', pos3);
        int points = std::stoi(line.substr(pos3, pos4 - pos3)); //s|to|i string to int

        //Extract options string (between 3rd and 4th pipe )
        size_t pos5 = pos4 + 1;
        size_t pos6 = line.find('|', pos5);
        std::string optionsStr = line.substr(pos5, pos6 - pos5);

        //Extract correct answer (everything after 4th pipe)
        std::string answer = line.substr(pos6 + 1);
        char correctAnswer = answer[0]; //First character is the answer;

        //Parse comma-seperated options into a vector
        // ex: op1,op2,op3,op4 -> {"op1", "op2", "op3", "op4"}
        std::vector<std::string> options;
        size_t start = 0;
        size_t comma = optionsStr.find(','); //Find first ','

        //Loop while there are more commas
        while(comma != std::string::npos){
            //Extract substring from start to comma
            options.push_back(optionsStr.substr(start, comma - start));
            start = comma + 1;
            comma = optionsStr.find(',', start); //find next comma
        }
        //add last option 
        options.push_back(optionsStr.substr(start));

        //Create and return new MultipleChoiceQuestion object
        return new MultipleChoiceQuestion(questionText, points, options, correctAnswer);
    }
    else if(type == "TF"){
        //Parse True/False Questions

        //Extract question text
        size_t pos1 = firstPipe + 1;
        size_t pos2 = line.find('|', pos1);
        std::string questionText = line.substr(pos1, pos2 - pos1);

        //Extract Points
        size_t pos3 = pos2 + 1;
        size_t pos4 = line.find('|', pos3);
        int points = std::stoi(line.substr(pos3, pos4 - pos3));

        //Extract Answer (true or false)
        std::string answerStr = line.substr(pos4 + 1);
        //Convert string to bool 
        bool correctAnswer = (answerStr == "true" || answerStr == "True" || answerStr == "TRUE");

        //Create and return new TrueFalseQuestion object
        return new TrueFalseQuestion(questionText, points, correctAnswer);
    }
    return nullptr; //Unknown question type
}

//Load questions from a file
bool QuizGame::load_from_file(std::string filename){
    //Create file input stream object
    std::ifstream file(filename); //ifstream = input file stream

    //check if file opened sucessfully
    if (!file.is_open()){
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    std::string line; //to store each line read;
    int loadedCount = 0; //Track how many questions loaded
    
    //Read file line by line until end
    //getline() returns false when end of file is reached

    while(std::getline(file, line)){
        //Try to parse this line into a question
        Question* q = parse_question_line(line);

        //If parsing succeeded (not nullptr)
        if (q != nullptr){
            add_question(q); //add to our questions vector
            loadedCount++; //increment counter
        }
    }
    file.close(); //Alwaxs close files when done

    //inform user how many questions were loaded
    std::cout << "Loaded " << loadedCount << " questions from " << filename << std::endl;

    return loadedCount > 0; //return true id at least one question was loaded
}

//========================
//HELPER METHODS - Phase 2
//========================
//Shuffle questions randomly
void QuizGame::shuffle_questions(){
    //Create random number generator

    std::random_device rd; //Seed from hardware
    std::mt19937 g(rd()); //Mersenne Twister engine

    //Shuffle the filtered questions
    std::shuffle(filteredQuestions.begin(), filteredQuestions.end(), g);

    std::cout << ColorTheme::CYAN << "🔀 Questions shuffled randomly!"
            << ColorTheme::RESET << std::endl;
}

//Filter questions by difficulty
void QuizGame::filter_by_difficulty(Difficulty diff){
    filteredQuestions.clear(); //Clear previous filter

    if (diff == MIXED){
        //No filter - inlcude all questions

        for (Question* q: questions){
            filteredQuestions.push_back(q);
        }
    }else{
        //Filter by point value
        for(Question* q: questions){
            if (q->get_points() == diff){
                filteredQuestions.push_back(q);
            }
        }
    }

    std::cout << ColorTheme::CYAN << "Filtered to " << filteredQuestions.size() << " questions(";

    if (diff == EASY) std::cout << "EASY";
    else if (diff == MEDIUM) std::cout << "MEDIUM";
    else if(diff == HARD) std::cout << "HARD";
    else std::cout << "MIXED";

    std::cout <<")" << ColorTheme::RESET << std::endl;
}

//Calculate bonus points for fast answers
int QuizGame::calculate_bonus_points(int basePoints, int secondsUsed, int timeLimit){
    //No bonus if timer not enabled
    if (!timerEnabled) return 0;

    //Fast answer = less than half the time
    if (secondsUsed < timeLimit / 2){
        return basePoints; //DOUBLE POINTS! (basepoints + basepoints)
    }
    return 0; //No bonus
}

//Apply 50/50 Lifeline to multiple choice questions
void QuizGame::apply_fifty_fifty(MultipleChoiceQuestion* mcq){
    
    std::cout << ColorTheme::YELLOW << "\n🎯 50/50 Activated!" 
            << ColorTheme::RESET << std::endl;

        //Get options and correct answer
        std::vector<std::string> options = mcq->get_options();
        char correctAnswer = mcq->get_correct_answer();

        //Find indices of wrong answers
        std::vector<int> wrongIndices;
        for(size_t i = 0; i < options.size(); i++){
            char optionLetter = 'A' + i;
            if (optionLetter != correctAnswer){
                wrongIndices.push_back(i);
            }
        }

    //Randomy selet 2 wrong answers to remove
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(wrongIndices.begin(), wrongIndices.end(), g);

    //Display which options are removed
    std::cout << ColorTheme::DIM << "Removing Wrong Answers: ";
    for (int i = 0; i < 2 && i < wrongIndices.size(); i++){
        char removedLetter = 'A' + wrongIndices[i];
        std::cout << removedLetter << " ";
    }
    std::cout << ColorTheme::RESET << std::endl;

    //Display remaining options ( correct + 1 wrong)
    std::cout << ColorTheme::GREEN << "\nRemaining options: \n";
    for (size_t i = 0; i < options.size(); i++){
        //Skip the 2 removed answers
        bool isRemoved = false;
        for(int j = 0; j < 2 && j < wrongIndices.size(); j++){
            if (i == wrongIndices[j]){
                isRemoved = true;
                break;
            }
        }
        if (!isRemoved){
            char letter = 'A' + i;
            std::cout << " " << letter << ". " << options[i] << std::endl;
        }
    }
    std::cout << ColorTheme::RESET << std::endl;
}

//=====================
//GAME SETTINGS METHODS
//=====================
//Set how many questions to ask
void QuizGame::set_question_count(int count){
    //validate range(50-300)
    if (count < 50) count = 50;
    if (count > 300) count = 300;

    totalQuestionsToAsk = count;
    std::cout << ColorTheme::CYAN << "Question count set to: " << count 
              << ColorTheme::RESET << std::endl;

    
}
//Set Difficulty Filter
void QuizGame::set_difficulty(Difficulty diff){
    selectedDifficulty = diff;

    std::cout << ColorTheme::CYAN << "Difficulty is set to: ";
    if (diff == EASY) std::cout << "EASY";
    else if(diff == MEDIUM) std::cout << "MEDIUM";
    else if(diff == HARD) std::cout << "HARD";
    else std::cout << "MIXED";
    std::cout << ColorTheme::RESET << std::endl;
}

//Enable timer with specified time limit
void QuizGame::enable_timer(int secondsPerQuestion){
    timerEnabled = true;
    questionTimeLimit = secondsPerQuestion;
    std::cout << ColorTheme::GREEN << "⏱️ Timer enabled: " << secondsPerQuestion
              << " seconds per question" << ColorTheme::RESET << std::endl;
}

//Disable Timer
void QuizGame::disable_timer(){
    timerEnabled = false;

    std::cout << ColorTheme::YELLOW << "⏱️ Timer Disabled(Practice Mode)"
             <<ColorTheme::RESET << std::endl;
}

//Enable Lifelines
void QuizGame::enable_lifelines(){
    lifelinesEnabled = true;
    lifelines.reset();
    
    std::cout << ColorTheme::GREEN << "💡 Lifelines enabled!" << ColorTheme::RESET << std::endl;
}

//Disable Lifelines
void QuizGame::disable_lifelines(){
    lifelinesEnabled = false;

    std::cout << ColorTheme::YELLOW << "💡 Lifelines Disabled (Hard Mode)"
             << ColorTheme::RESET << std::endl;
}

//Set game mode
void QuizGame::set_game_mode(Gamemode mode){
    currentGameMode = mode;

    std::cout << ColorTheme::GREEN << "✓ Game mode set to: ";

    switch (mode){
        case CLASSIC:
            std::cout << "Classic (Configurable)" << ColorTheme::RESET << std::endl;
            break;
        case QUICK_ATTACK: 
            std::cout << "Quick Attack (5 min time limit)" << ColorTheme::RESET << std::endl;
            break;
        case SURVIVAL:
            std::cout << "Survival (3 lives)" << ColorTheme::RESET << std::endl;
            break;
        case MARATHON:
            std::cout << "Marathon (All 300 questions)" << ColorTheme::RESET << std::endl;
            break;
        case LIGHTNING:
            std::cout << "Lightning round(10s per question)" << ColorTheme::RESET << std::endl;
            break;
        case PRACTICE:
            std::cout << "Practice Mode (No Pressure)" << ColorTheme::RESET << std::endl;
            break;
    }
    
}

//====================
//MENU SYSTEM -Phase 2
//====================

//Main Menu with flashy interface
void QuizGame::show_main_menu(){
    std::cout << "\n\n";
    ColorTheme::print_separator();
    ColorTheme::print_separator();

    //Title
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n";
    std::cout << "    ╔═══════════════════════════════════════╗\n";
    std::cout << "    ║                                       ║\n";
    std::cout << "    ║        🎮 MAIN MENU 🎮                ║\n";
    std::cout << "    ║                                       ║\n";
    std::cout << "    ╚═══════════════════════════════════════╝\n";
    std::cout << ColorTheme::RESET << "\n";

    //options
    std::cout << ColorTheme::GREEN << "    ▸ " << ColorTheme::BOLD << "[1]"
             << ColorTheme::RESET << ColorTheme::GREEN << " Start New Quiz"
            << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::YELLOW << "    ▸ " << ColorTheme::BOLD << "[2]" 
             << ColorTheme::RESET << ColorTheme::YELLOW << " Configure Settings"
             << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::RED << "    ▸ " << ColorTheme::BOLD << "[3]"
              << ColorTheme::RESET << ColorTheme::RED << "Exit Game"
              << ColorTheme::RESET << std::endl;
    std::cout << "\n";
    ColorTheme::print_separator();
}

//Game mode selection menu
void QuizGame::show_game_mode_menu(){
    std::cout << "\n\n";
    ColorTheme::print_separator();
    ColorTheme::print_separator();

    //Title
    std::cout << ColorTheme::CYAN << ColorTheme::BOLD;
    std::cout << "\n";
    std::cout << "    ╔═══════════════════════════════════════════╗\n";
    std::cout << "    ║                                           ║\n";
    std::cout << "    ║        🎮 SELECT GAME MODE 🎮             ║\n";
    std::cout << "    ║                                           ║\n";
    std::cout << "    ╚═══════════════════════════════════════════╝\n";
    std::cout << ColorTheme::RESET << "\n";

    //Mode 1: Classic
    std::cout << ColorTheme::GREEN << "    ▸ " << ColorTheme::BOLD << "[1]" 
    << ColorTheme::RESET << ColorTheme::GREEN << " 🎯 Classic Mode" 
    << ColorTheme::RESET << std::endl;
    
    std::cout << ColorTheme::DIM << "      Fully customizable quiz experience"
    << ColorTheme::RESET << "\n\n";

    //Mode 2:Quick Attack
    std::cout << ColorTheme::YELLOW << "    ▸ " << ColorTheme::BOLD << "[2]" 
    << ColorTheme::RESET << ColorTheme::YELLOW << " ⚡ Quick Attack" << ColorTheme::RESET
    << std::endl;

    std::cout << ColorTheme::DIM << "      5 Minutes ° Wrong = -15s ° Race against time!"
    << ColorTheme::RESET << "\n\n";

    //Mode 3: Survival
    std::cout << ColorTheme::RED << "    ▸ " << ColorTheme::BOLD << "[3]" << ColorTheme::RESET
    << ColorTheme::RED << " 💀 Survival Mode" << ColorTheme::RESET << std::endl;

    std::cout << ColorTheme::DIM << "      3 Lives ° One mistake closer to game over"
    << ColorTheme::RESET << "\n\n";

    //Mode 4: Marathon
    std::cout << ColorTheme::MAGENTA << "    ▸ " << ColorTheme::BOLD << "[4]" << ColorTheme::RESET
    << ColorTheme::MAGENTA << " 🏃 Marathon Mode" << ColorTheme::RESET << std::endl;

    std::cout << ColorTheme::DIM << "      All 300 questions ° Can you Finish?" << ColorTheme::RESET << "\n\n";

    //Mode 5: Lightning
    std::cout << ColorTheme::CYAN << "    ▸ " << ColorTheme::BOLD << "[5]" << ColorTheme::RESET
    << ColorTheme::CYAN << " ⚡ Lightning Round" << ColorTheme::RESET << std::endl;

    std::cout << ColorTheme::DIM << "      10 seconds per question ° Think fast!"
    << ColorTheme::RESET << "\n\n";

    //Mode 6: Practice
    std::cout << ColorTheme::BLUE << "    ▸ " << ColorTheme::BOLD << "[6]" << ColorTheme::RESET
    << ColorTheme::BLUE << " 📚 Practice Mode" << ColorTheme::RESET << std::endl;

    std::cout << ColorTheme::DIM << "      No Pressure ° See answers ° Learn!"
    << ColorTheme::RESET << "\n\n";

    std::cout << "\n";
    ColorTheme::print_separator();

}

  // Interactive configuration menu
  void QuizGame::configure_game() {
    std::cout << "\n";
    ColorTheme::print_separator();

    // Header
    std::cout << ColorTheme::MAGENTA << ColorTheme::BOLD;
    std::cout << "\n    ⚙️   GAME CONFIGURATION ⚙️ \n" << ColorTheme::RESET;
    ColorTheme::print_separator();

    // 1. Question Count - Fixed for Marathon mode
    if (currentGameMode == MARATHON) {
        // Marathon: All 300 questions (FIXED)
        set_question_count(300);
        std::cout << ColorTheme::CYAN << "\n[1] Question Count" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::YELLOW << "🏃 Marathon Mode: ALL 300 questions (FIXED)"
                  << ColorTheme::RESET << std::endl;
    } else {
        // Other modes: User can choose
        std::cout << ColorTheme::CYAN << "\n[1] Question Count" << ColorTheme::RESET << std::endl;
        std::cout << "    Choose: ";
        std::cout << ColorTheme::DIM << "50 | 100 | 150 | 200 | 250 | 300" << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::YELLOW << "    Your choice: " << ColorTheme::RESET;

        int count;
        std::cin >> count;
        std::cin.ignore(); // Clear newline
        set_question_count(count);
    }

    // 2. Difficulty
    std::cout << ColorTheme::CYAN << "\n[2] Difficulty Level" << ColorTheme::RESET << std::endl;
    std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - Easy (5 pts)\n";
    std::cout << "    " << ColorTheme::YELLOW << "2" << ColorTheme::RESET << " - Medium (10 pts)\n";
    std::cout << "    " << ColorTheme::RED << "3" << ColorTheme::RESET << " - Hard (15 pts)\n";
    std::cout << "    " << ColorTheme::CYAN << "4" << ColorTheme::RESET << " - Mixed (All)\n";
    std::cout << ColorTheme::YELLOW << "    Your choice: " << ColorTheme::RESET;

    int diffChoice;
    std::cin >> diffChoice;
    std::cin.ignore();

    switch(diffChoice) {
        case 1: set_difficulty(EASY); break;
        case 2: set_difficulty(MEDIUM); break;
        case 3: set_difficulty(HARD); break;
        case 4:
        default: set_difficulty(MIXED); break;
    }

   // 3. Timer - Skip for modes with fixed timing
   if (currentGameMode == LIGHTNING) {
       // Lightning: Fixed 10 seconds per question
       enable_timer(10);
       std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
       std::cout << "    " << ColorTheme::YELLOW << "⚡ Lightning Mode: 10 seconds per question (FIXED)"
                 << ColorTheme::RESET << std::endl;
   } else if (currentGameMode == QUICK_ATTACK) {
       // Quick Attack: Uses GlobalTimer (5 min countdown), not per-question timer
       disable_timer();
       std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
       std::cout << "    " << ColorTheme::YELLOW << "🏃 Quick Attack: 5-minute countdown (FIXED)"
                 << ColorTheme::RESET << std::endl;
   } else if (currentGameMode == PRACTICE) {
       // Practice: No pressure mode
       disable_timer();
       std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
       std::cout << "    " << ColorTheme::GREEN << "📚 Practice Mode: No timer (learn at your pace)"
                 << ColorTheme::RESET << std::endl;
   } else {
       // Classic, Marathon, Survival: User can choose
       std::cout << ColorTheme::CYAN << "\n[3] Timer Mode" << ColorTheme::RESET << std::endl;
       std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - No Timer (Practice)\n";
       std::cout << "    " << ColorTheme::YELLOW << "2" << ColorTheme::RESET << " - 60 seconds per question\n";
       std::cout << "    " << ColorTheme::RED << "3" << ColorTheme::RESET << " - 30 seconds per question\n";
       std::cout << "    " << ColorTheme::MAGENTA << "4" << ColorTheme::RESET << " - 15 seconds per question(Hard!)\n";
       std::cout << ColorTheme::YELLOW << "    Your choice: " << ColorTheme::RESET;

       int timerChoice;
       std::cin >> timerChoice;
       std::cin.ignore();

       switch(timerChoice) {
           case 1: disable_timer(); break;
           case 2: enable_timer(60); break;
           case 3: enable_timer(30); break;
           case 4: enable_timer(15); break;
           default: disable_timer(); break;
       }
   }

    // 4. Lifelines - Skip for modes where they don't make sense
    if (currentGameMode == PRACTICE) {
        // Practice: No pressure = no need for lifelines
        disable_lifelines();
        std::cout << ColorTheme::CYAN << "\n[4] Lifelines" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::GREEN << "📚 Practice Mode: Lifelines disabled (you'll see correct answers anyway)"
                  << ColorTheme::RESET << std::endl;
    } else if (currentGameMode == QUICK_ATTACK) {
        // Quick Attack: Speed mode = no time for lifelines
        disable_lifelines();
        std::cout << ColorTheme::CYAN << "\n[4] Lifelines" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::YELLOW << "🏃 Quick Attack: Lifelines disabled (speed is key!)"
                  << ColorTheme::RESET << std::endl;
    } else {
        // Other modes: User can choose
        std::cout << ColorTheme::CYAN << "\n[4] Lifelines" << ColorTheme::RESET << std::endl;
        std::cout << "    " << ColorTheme::GREEN << "1" << ColorTheme::RESET << " - Enabled (50/50, Skip)\n";
        std::cout << "    " << ColorTheme::RED << "2" << ColorTheme::RESET << " - Disabled (Hard Mode)\n";
        std::cout << ColorTheme::YELLOW << "    Your choice: " << ColorTheme::RESET;

        int lifelineChoice;
        std::cin >> lifelineChoice;
        std::cin.ignore();

        if (lifelineChoice == 1) {
            enable_lifelines();
        } else {
            disable_lifelines();
        }
    }

    // Summary
    std::cout << "\n";
    ColorTheme::print_separator();
    std::cout << ColorTheme::GREEN << ColorTheme::BOLD;
    std::cout << "    ✓ Configuration Complete!" << ColorTheme::RESET << std::endl;
    ColorTheme::print_separator();

    std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
    std::cin.get();
 }

  // Check for saved game and prompt user
bool QuizGame::prompt_load_save() {
    if (!has_saved_game()) {
        return false;  // No save found
    }

    // Flashy save detected screen
    std::cout << "\n\n";
    ColorTheme::print_separator();

    std::cout << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << "\n    💾 SAVED GAME DETECTED! 💾\n" << ColorTheme::RESET;

    ColorTheme::print_separator();

    std::cout << ColorTheme::CYAN;
    std::cout << "\n    A saved game was found!\n";
    std::cout << "    You can continue where you left off.\n";
    std::cout << ColorTheme::RESET;

    std::cout << "\n";
    std::cout << ColorTheme::GREEN << "    [1]" << ColorTheme::RESET
              << " Continue Saved Game 📂\n";
    std::cout << ColorTheme::RED << "    [2]" << ColorTheme::RESET
              << " Start New Game (Erase Save) 🗑️ \n";

    std::cout << "\n";
    ColorTheme::print_separator();
    std::cout << ColorTheme::YELLOW << "    Your choice: " << ColorTheme::RESET;

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
       // Load saved game
        if (load_game("savegame.dat")) {
            std::cout << ColorTheme::GREEN << "\n    ✓ Save loaded successfully!"
                      << ColorTheme::RESET << std::endl;
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..."
                      << ColorTheme::RESET;
            std::cin.get();
            return true;
        } else {
            std::cout << ColorTheme::RED << "\n    ✗ Failed to load save!"
                      << ColorTheme::RESET << std::endl;
            return false;
        }
    } else {
        // Delete save and start fresh
        delete_save();
        std::cout << ColorTheme::YELLOW << "\n    🗑️   Save deleted. Starting fresh!"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::DIM << "\nPress Enter to continue..."
                  << ColorTheme::RESET;
        std::cin.get();
        return false;
    }
}

//=========================
//SAVE/LOAD SYSTEM - Phse 2
//=========================
//
//Check if File exists
bool QuizGame::has_saved_game()const{
    std::ifstream file("savegame.dat");
    return file.good(); //Returns true if file exists and is readable
}

//Delete save file
void QuizGame::delete_save(){
    std::remove("savegame.dat"); //C Function to delete file

    std::cout << ColorTheme::YELLOW << "💾 Save File Deleted."
              << ColorTheme::RESET << std::endl;
}

  // Save current game state to file
bool QuizGame::save_game(std::string filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << ColorTheme::RED << "Error: Could not create save file!"
                  << ColorTheme::RESET << std::endl;
        return false;
    }

    // Write save file header
    file << "# CodeMaster Quiz Save File\n";
    file << "VERSION=1.0\n";
    file << "\n# Progress\n";
    file << "CURRENT_QUESTION=" << currentQuestionIndex << "\n";
    file << "TOTAL_QUESTIONS=" << totalQuestionsToAsk << "\n";
    file << "\n# Scores\n";
    file << "EARNED_SCORE=" << earnedScore << "\n";
    file << "TOTAL_SCORE=" << totalScore << "\n";
    file << "CORRECT_COUNT=" << correctCount << "\n";
    file << "\n# Streaks\n";
    file << "CURRENT_STREAK=" << currentStreak << "\n";
    file << "BEST_STREAK=" << bestStreak << "\n";
    file << "TOTAL_BONUS=" << totalBonusPoints << "\n";
    file << "\n# Settings\n";
    file << "DIFFICULTY=" << selectedDifficulty << "\n";
    file << "TIMER_ENABLED=" << (timerEnabled ? "true" : "false") << "\n";
    file << "TIME_LIMIT=" << questionTimeLimit << "\n";
    file << "LIFELINES_ENABLED=" << (lifelinesEnabled ? "true" : "false") << "\n";
    file << "\n# Lifeline States\n";
    file << "LIFELINE_5050_USED=" << (lifelines.is_fifty_fifty_used() ? "true" : "false") << "\n";
    file << "LIFELINE_SKIP_USED=" << (lifelines.is_skip_used() ? "true" : "false") << "\n";
    file << "LIFELINE_HINT_USED=" << (lifelines.is_hint_used() ? "true" : "false") << "\n";

    file.close();

    std::cout << ColorTheme::GREEN << "\n💾 Game saved successfully!"
              << ColorTheme::RESET << std::endl;

    return true;
}

// Load saved game state from file
bool QuizGame::load_game(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << ColorTheme::RED << "Error: Could not open save file!"
                  << ColorTheme::RESET << std::endl;
        return false;
    }

    std::string line;

    // Read file line by line
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;
        // Find the = separator
        size_t equals = line.find('=');
        if (equals == std::string::npos) continue;

        // Extract key and value
        std::string key = line.substr(0, equals);
        std::string value = line.substr(equals + 1);

        // Parse each setting
        if (key == "CURRENT_QUESTION") {
            currentQuestionIndex = std::stoi(value);
        }
        else if (key == "TOTAL_QUESTIONS") {
            totalQuestionsToAsk = std::stoi(value);
        }
        else if (key == "EARNED_SCORE") {
            earnedScore = std::stoi(value);
        }
        else if (key == "TOTAL_SCORE") {
            totalScore = std::stoi(value);
        }
        else if (key == "CORRECT_COUNT") {
            correctCount = std::stoi(value);
        }
        else if (key == "CURRENT_STREAK") {
            currentStreak = std::stoi(value);
        }
        else if (key == "BEST_STREAK") {
            bestStreak = std::stoi(value);
        }
        else if (key == "TOTAL_BONUS") {
            totalBonusPoints = std::stoi(value);
        }
        else if (key == "DIFFICULTY") {
            selectedDifficulty = static_cast<Difficulty>(std::stoi(value));
        }
        else if (key == "TIMER_ENABLED") {
            timerEnabled = (value == "true");
        }
        else if (key == "TIME_LIMIT") {
            questionTimeLimit = std::stoi(value);
        }
        else if (key == "LIFELINES_ENABLED") {
            lifelinesEnabled = (value == "true");
        }
        else if (key == "LIFELINE_5050_USED") {
            lifelines.set_fifty_fifty_used(value == "true");
        }
        else if (key == "LIFELINE_SKIP_USED") {
            lifelines.set_skip_used(value == "true");
        }
        else if (key == "LIFELINE_HINT_USED") {
            lifelines.set_hint_used(value == "true");
        }
    }
    file.close();

    std::cout << ColorTheme::GREEN << "\n💾 Game loaded successfully!"
              << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::CYAN << "Resuming at question " << (currentQuestionIndex + 1)
              << " of " << totalQuestionsToAsk << ColorTheme::RESET << std::endl;

    return true;
}


