#include <iostream>
#include <cctype>
#include <fstream>   // For file I/O
#include <sstream>   // For string parsing
#include "quiz.h"


//===========================================
//COLOR THEME CLASS: Static Color Definitions
//===========================================

//Define all the static ANSI Color Codes
//These are escape sequences that terminals interpret as colors

const char* ColorTheme::RESET = "\033[0m"; //Reset to default
const char* ColorTheme::RED = "\033[31m";   //Red text
const char* ColorTheme::GREEN = "\033[32m"; //Green text
const char* ColorTheme::YELLOW = "\033[33m";    //Yellow text
const char* ColorTheme::BLUE = "\033[34m";  //Blue text
const char* ColorTheme::MAGENTA = "\033[35m";   //Magenta text
const char* ColorTheme::CYAN = "\033[36m";  //Cyan text
const char* ColorTheme::BOLD = "\033[1m";   //Bold text
const char* ColorTheme::DIM = "\033[2m";    //Dimmed text


//Print the game banner - called at the start
void ColorTheme::print_banner(){

    std::cout << CYAN << BOLD;
    std::cout << R"(      
      ╔════════════════════════════════════════════════╗
      ║                                                ║
      ║     ██████╗ ██╗   ██╗██╗███████╗               ║
      ║    ██╔═══██╗██║   ██║██║╚══███╔╝               ║
      ║    ██║   ██║██║   ██║██║  ███╔╝                ║
      ║    ██║▄▄ ██║██║   ██║██║ ███╔╝                 ║
      ║    ╚██████╔╝╚██████╔╝██║███████╗               ║
      ║     ╚══▀▀═╝  ╚═════╝ ╚═╝╚══════╝               ║
      ║                                                ║
      ║           CODEMASTER C++ QUIZ                  ║
      ║        Test Your Programming Skills!           ║
      ║                                                ║
      ╚════════════════════════════════════════════════╝
      )" << RESET << std::endl;
}

//Print seperator line
void ColorTheme::print_separator(){
    std::cout << DIM << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << std::endl;
}

//Print correct answer message with points
void ColorTheme::print_correct_message(int points){
    std::cout << GREEN << BOLD << " ✓ CORRECT!" << RESET;
    std::cout << GREEN << "+" << points << " points" << RESET << std::endl;
}

//Print wrong answer message
void ColorTheme::print_wrong_message(){
    std::cout << RED << BOLD << " ✗ WRONG!" << RESET << std::endl;
} 

//Print question header with number
void ColorTheme::print_question_header(int current, int total){
    std::cout << "\n" << YELLOW << BOLD << "╔═══ Question " << current << " of " << total << " ═══╗" << RESET << std::endl;
}

// Print progress bar showing quiz completion
void ColorTheme::print_progress_bar(int current, int total){
    int barWidth = 40; //Width of the progress bar in charecters
    float progress = (float)current/total; //Percentage calculation

    std::cout << CYAN << "Progress [";

    //Calculate how many "filled" blocks to show
    int filled = barWidth * progress;

    //Draw progress bar
    for (int i = 0; i < barWidth; i++){
        if (i < filled){
            std::cout << "█"; //Filled block
        }else {
            std::cout << "░"; //empty block
        }
    }

    //Show percentage of progress
    std::cout << "] " << int(progress * 100.0) << "%" << RESET << std::endl;
}



//====================================
//BASE CLASSE: Question Implementation
//====================================

//Constructor - Initializes questionText and points
Question::Question(std::string text, int pts)
    :questionText(text), points(pts){

    }

//Virtual Destructor
Question::~Question(){
    //Empty but necessary for proper inheritance cleanup
    //When a child object is deleted through a base pointer
    //this ensures the chain of destructors is called properly
}

//Points getter
int Question::get_points(){
    return points;
}


//=====================================
//CHILD CLASS 1: MultipleChoiceQuestion
//=====================================

//Constructor - calls parent constructor, the initializes child members
MultipleChoiceQuestion::MultipleChoiceQuestion(std::string text, int pts, std::vector<std::string> opts, char correct)
    :Question(text, pts), //call Parent constructo first
     options(opts), //Initialize options vector
     correctAnswer(correct){ //Initialize correctAnswer
        //Constructor body (empty - initializer list did everything)
     }

//Destructor
MultipleChoiceQuestion::~MultipleChoiceQuestion(){
    //No Manual cleanup needed
    //vector<string> automatically cleans itself up
}

//Display the question and options
void MultipleChoiceQuestion::display(){
    std::cout << "\n" << questionText << " (" << points << " points)" << std::endl;

    //Diplay each option with its letter
    for(size_t i = 0; i < options.size(); i++)
    {
        char letter = 'A' + i; //'A' + 0 = 'A', 'A' + 1 = 'B', etc.
        std::cout << " " << letter << ". " << options[i] << std::endl;
    }
    std::cout << "Your answer: ";
}

//Check if the user's answer is correct
bool MultipleChoiceQuestion::checkAnswer(std::string answer){
    //convert answer to uppercase for case-insensitive comparison
    if (answer.length() != 1) return false; //Must be single character

    char userAnswer = toupper(answer[0]); //Convert to uppercase
    return userAnswer == correctAnswer; //Compare with correct answer
}

//================================
//CHILD CLASS 2: TrueFalseQuestion
//================================

//Constructor - calls parent constructor, then initializes child members
TrueFalseQuestion::TrueFalseQuestion(std::string text, int pts, bool correct)
    :Question(text, pts), //Call parent constructor
    correctAnswer(correct){ //Initialize correct answer
            //Constructor body (empty)
    }

//Destructor
TrueFalseQuestion::~TrueFalseQuestion(){
    //No Manual Clean up needed
}

//Display the question
void TrueFalseQuestion::display(){
    std::cout << "\n" << questionText << " (" << points << " points)" << std::endl;
    std::cout << "True or False?" << std::endl;
    std::cout << "Your answer (T/F): ";
}

//Check if the user's answer is correct
bool TrueFalseQuestion::checkAnswer(std::string answer){
    if (answer.empty()) return false; //Empty answer is wrong

    char userAnswer = toupper(answer[0]); //Get first char, uppercase

    //Convert 'T' or 'F' to bool and compare
    if (userAnswer == 'T'){
        return correctAnswer == true;
    }
    else if(userAnswer == 'F'){
        return correctAnswer == false;
    }

    return false; //Invalid input (not T or F)
}

//============================
//GAME MANAGER CLASS: QuizGame
//============================

//Constructor - initializes the game with 0 points
QuizGame::QuizGame()
    :totalScore(0), earnedScore(0), correctCount(0), currentStreak(0), bestStreak(0){
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


//Run the entire quiz game
void QuizGame::run(){
    //Display Flashy Banner
    ColorTheme::print_banner();

    std::cout << ColorTheme::BOLD << "Total Questions: " << questions.size() << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::DIM << "Answer carefully and build your streak!\n" << ColorTheme::RESET << std::endl;

    //Reset Scores and stats to 0 (in case run() is called multiple times)
    totalScore = 0;
    earnedScore = 0;
    correctCount = 0;
    currentStreak = 0;
    bestStreak = 0;

    //Loop through all questions using index
    for(size_t i = 0; i < questions.size(); i++)
    {
        Question* q = questions[i]; //Get pointer to current question

        //Show progress bar
        ColorTheme::print_progress_bar(i, questions.size());

        //Question header with colors
        ColorTheme::print_question_header(i + 1, questions.size());

        //Display the question (Polymorphism)
        q->display();

        //Get user input
        std::string userAnswer;
        std::getline(std::cin, userAnswer);

        //Check if answer is correct
        if (q->checkAnswer(userAnswer)){
            ColorTheme::print_correct_message(q->get_points());
            earnedScore += q->get_points();
            correctCount++;
            currentStreak++; //Increment streak;

            //Uodate best streak
            if (currentStreak > bestStreak) {
                bestStreak = currentStreak;
            }
            //Streak milestones
            if (currentStreak == 3){
                std::cout << ColorTheme::YELLOW << " 🔥 3 in a Row! Keep it up!" << ColorTheme::RESET << std::endl;
            } else if (currentStreak == 5) {
                std::cout << ColorTheme::MAGENTA << " ⚡ 5 STREAK! You're on fire!" << ColorTheme::RESET << std::endl;
            } else if (currentStreak == 10) {
                std::cout << ColorTheme::RED << ColorTheme::BOLD << " 💥 10 STREAK! UNSTOPPABLE!" << ColorTheme::RESET << std::endl;
            }
        }
        else {
            ColorTheme::print_wrong_message();
            currentStreak = 0; //Reset Current Streak to 0 when wrong answer
        }
        //Track total possible points
        totalScore += q->get_points();

        //Show stats every 5 questions
        if ((i + 1) % 5 == 0 && (i + 1) < questions.size()){
            display_live_stats(i + 1, questions.size());
            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.get(); //Wait for user to press Enter
        }
    }

    //After all questions, show results
    display_results();
    //Show Achievements
    display_achievements();
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
    std::cout << correctCount << " / " << questions.size() << ColorTheme::RESET << std::endl;

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
    std::cout << "\n" << ColorTheme::YELLOW << ColorTheme::BOLD;
    std::cout << "🏆 ACHIEVEMENTS: " << ColorTheme::RESET << std::endl;

    //Perfect Score
    if (earnedScore == totalScore){
        std::cout << ColorTheme::GREEN << " ⭐ PERFECT SCORE - Flawless Victory!" << ColorTheme::RESET << std::endl;
    }

    //high Streak achievements
    if (bestStreak >= 10){
        std::cout << ColorTheme::MAGENTA << " 🔥 ON FIRE - 10+ Question Streak!" << ColorTheme::RESET << std::endl;
    }else if (bestStreak >= 5) {
        std::cout << ColorTheme::CYAN << " ⚡ HOT STREAK - 5+ Questions in a row!" << ColorTheme::RESET << std::endl;
    }

    //Accuracy Achievements
    double accuracy = (double)correctCount / questions.size() * 100.0;
    if (accuracy >= 90.0) {
        std::cout << ColorTheme::GREEN << " 🎯 SHARPSHOOTER - 90%+ Accuracy!" << ColorTheme::RESET << std::endl;
    } else if (accuracy >= 75.0) {
        std::cout << ColorTheme::BLUE << " 📚 SCHOLAR - 75%+ Accuracy!" << ColorTheme::RESET << std::endl;
    }

    //Completion Achievement
    std::cout << ColorTheme::CYAN << " ✅ QUIZ COMPLETED - " << questions.size() << " Questions Answered!" << ColorTheme::RESET << std::endl;
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