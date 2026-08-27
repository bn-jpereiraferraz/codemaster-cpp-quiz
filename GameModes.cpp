#include "GameModes.h"
#include "QuizGame.h"
#include "ColorTheme.h"
#include "Timer.h" 
#include "GlobalTimer.h"
#include "Lives.h"
#include "MultipleChoiceQuestion.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

void GameModes::run_classic(QuizGame& game){
    // Display banner
    ColorTheme::print_banner();

    std::cout << "\n" << ColorTheme::CYAN << ColorTheme::BOLD
              << "📚 Welcome to CodeMaster Quiz!" << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::DIM << "Test your C++ knowledge and earn achievements!\n"
              << ColorTheme::RESET;
    ColorTheme::print_separator();

    // Check if questions loaded
    if (game.questions.empty()) {
        std::cerr << ColorTheme::RED << "Error: No questions loaded!"
                  << ColorTheme::RESET << std::endl;
        return;
    }

    // Save loaded scores/progress before filtering (in case we're resuming)
    int savedEarnedScore = game.earnedScore;
    int savedCorrectCount = game.correctCount;
    int savedCurrentStreak = game.currentStreak;
    int savedBestStreak = game.bestStreak;
    int savedBonusPoints = game.totalBonusPoints;
    int savedQuestionIndex = game.currentQuestionIndex;

    // Apply difficulty filter and shuffle
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    // Limit to requested count
    if (game.filteredQuestions.size() > static_cast<size_t>(game.totalQuestionsToAsk)) {
        game.filteredQuestions.resize(game.totalQuestionsToAsk);
    }

    // Calculate total possible score
    game.totalScore = 0;
    for (Question* q : game.filteredQuestions) {
        game.totalScore += q->get_points();
    }

    // Restore loaded progress if we were resuming from save
    game.earnedScore = savedEarnedScore;
    game.correctCount = savedCorrectCount;
    game.currentStreak = savedCurrentStreak;
    game.bestStreak = savedBestStreak;
    game.totalBonusPoints = savedBonusPoints;
    game.currentQuestionIndex = savedQuestionIndex;

    std::cout << ColorTheme::YELLOW << "\n🎯 Quiz configured:" << ColorTheme::RESET << std::endl;
    std::cout << "   Questions: " << ColorTheme::BOLD << game.filteredQuestions.size()
              << ColorTheme::RESET << std::endl;
    std::cout << "   Total Points: " << ColorTheme::BOLD << game.totalScore
              << ColorTheme::RESET << std::endl;

    if (game.timerEnabled) {
        std::cout << "   Timer: " << ColorTheme::RED << game.questionTimeLimit
                  << " seconds per question" << ColorTheme::RESET << std::endl;
    }

    if (game.lifelinesEnabled) {
        std::cout << "   Lifelines: " << ColorTheme::GREEN << "Enabled 💡"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::DIM << "   → Type '5050' to remove 2 wrong answers (MC only)\n";
        std::cout << "   → Type 'skip' to skip a question without penalty" << ColorTheme::RESET << std::endl;
    }

    std::cout << "\n" << ColorTheme::DIM << "Press Enter to begin..."
              << ColorTheme::RESET;
    std::cin.get();

    // Main quiz loop
    for (size_t i = game.currentQuestionIndex; i < game.filteredQuestions.size(); i++) {
        game.currentQuestionIndex = i;  // Update for saving
        Question* q = game.filteredQuestions[i];

        // Clear screen effect
        std::cout << "\n\n\n";

        // Display question header
        ColorTheme::print_question_header(i + 1, game.filteredQuestions.size());
        ColorTheme::print_progress_bar(i + 1, game.filteredQuestions.size());

        // Show lifelines if enabled
        if (game.lifelinesEnabled) {
            game.lifelines.display_available();
        }

        std::cout << "\n";

        // Display question
        q->display();

        // Check if this is a Multiple Choice question (for 50/50)
        MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(q);

        // Start timer if enabled
        Timer questionTimer(game.questionTimeLimit);
        if (game.timerEnabled) {
            questionTimer.start();
            std::cout << ColorTheme::YELLOW << "\n⏱️  Timer: " << game.questionTimeLimit
                      << " seconds" << ColorTheme::RESET << std::endl;
        }

        // Get user answer (with lifeline options)
        std::string answer;
        bool skipped = false;
        bool usedFiftyFifty = false;

        while (true) {
            std::cout << ColorTheme::CYAN << "\nYour answer";

            // Show lifeline shortcuts
            if (game.lifelinesEnabled) {
                std::cout << ColorTheme::DIM << " (or ";
                if (game.lifelines.can_use_fifty_fifty() && mcq) {
                    std::cout << "'5050' for 50/50";
                }
                if (game.lifelines.can_use_skip()) {
                    if (game.lifelines.can_use_fifty_fifty() && mcq) std::cout << ", ";
                    std::cout << "'skip'";
                }
                std::cout << ")";
            }

            std::cout << ColorTheme::RESET << ": ";
            std::getline(std::cin, answer);

            // Convert to lowercase for comparison
            std::string lowerAnswer = answer;
            for (char& c : lowerAnswer) c = tolower(c);

            // Check for lifeline usage
            if (lowerAnswer == "5050" && game.lifelines.can_use_fifty_fifty() && mcq) {
                if (game.lifelines.use_fifty_fifty()) {
                    game.apply_fifty_fifty(mcq);
                    usedFiftyFifty = true;
                    continue;  // Ask for answer again
                }
            }
            else if (lowerAnswer == "skip" && game.lifelines.can_use_skip()) {
                if (game.lifelines.use_skip()) {
                    std::cout << ColorTheme::YELLOW << "\n⏭️  Question skipped!"
                              << ColorTheme::RESET << std::endl;
                    skipped = true;
                    break;
                }
            }
            else {
                // Validate answer format before accepting it
                if (mcq) {
                    // Multiple choice - must be A, B, C, or D
                    if (answer.length() == 1) {
                        char upperAnswer = toupper(answer[0]);
                        if (upperAnswer >= 'A' && upperAnswer <= 'D') {
                            break;  // Valid answer!
                        }
                    }
                    // Invalid format - show error and ask again
                    std::cout << ColorTheme::RED << "❌ Invalid input! Please enter A, B, C, or D."
                              << ColorTheme::RESET << std::endl;
                    continue;
                }
                else {
                    // True/False question - must be "true" or "false"
                    if (lowerAnswer == "true" || lowerAnswer == "false" ||
                        lowerAnswer == "t" || lowerAnswer == "f") {
                        break;  // Valid answer!
                    }
                    // Invalid format - show error and ask again
                    std::cout << ColorTheme::RED << "❌ Invalid input! Please enter 'true' or 'false'."
                              << ColorTheme::RESET << std::endl;
                    continue;
                }
            }
        }

        // Stop timer
        int secondsUsed = 0;
        if (game.timerEnabled) {
            questionTimer.stop();
            secondsUsed = questionTimer.get_elapsed_seconds();
        }

        // Check answer (if not skipped)
        if (!skipped) {
            bool correct = q->checkAnswer(answer);
            int basePoints = q->get_points();

            if (correct) {
                // Calculate bonus points for speed
                int bonusPoints = 0;
                if (game.timerEnabled) {
                    bonusPoints = game.calculate_bonus_points(basePoints, secondsUsed, game.questionTimeLimit);
                    game.totalBonusPoints += bonusPoints;
                }

                game.earnedScore += basePoints + bonusPoints;
                game.correctCount++;
                game.currentStreak++;

                if (game.currentStreak > game.bestStreak) {
                    game.bestStreak = game.currentStreak;
                }

                // Display success message
                ColorTheme::print_correct_message(basePoints);

                if (bonusPoints > 0) {
                    std::cout << ColorTheme::MAGENTA << "⚡ SPEED BONUS: +"
                              << bonusPoints << " points! (" << secondsUsed
                              << "s)" << ColorTheme::RESET << std::endl;
                }

                // Streak milestones
                if (game.currentStreak == 3) {
                    std::cout << ColorTheme::YELLOW << "🔥 3-STREAK! You're on fire!"
                              << ColorTheme::RESET << std::endl;
                }
                else if (game.currentStreak == 5) {
                    std::cout << ColorTheme::YELLOW << "🔥🔥 5-STREAK! Unstoppable!"
                              << ColorTheme::RESET << std::endl;
                }
                else if (game.currentStreak == 10) {
                    std::cout << ColorTheme::YELLOW << "🔥🔥🔥 10-STREAK! LEGENDARY!"
                              << ColorTheme::RESET << std::endl;
                }
            }
            else {
                // Wrong answer
                ColorTheme::print_wrong_message();
                game.currentStreak = 0;  // Reset streak
            }
        }

        // Live stats every 5 questions
        if ((i + 1) % 5 == 0 && i + 1 < game.filteredQuestions.size()) {
            game.display_live_stats(i + 1, game.filteredQuestions.size());

            // Auto-save every 5 questions
            game.save_game("savegame.dat");

            std::cout << ColorTheme::DIM << "\nPress Enter to continue..."
                      << ColorTheme::RESET;
            std::cin.get();
        }
        else {
            // Small pause between questions
            std::cout << ColorTheme::DIM << "\nPress Enter for next question..."
                      << ColorTheme::RESET;
            std::cin.get();
        }
    }

    // Quiz complete - delete save file
    game.delete_save();

    // Display final results
    game.display_results();
    game.display_achievements();
}

//=======================================
//RUN QUICK ATTACK 5 Minute Time Attack
//=======================================
void GameModes::run_quick_attack(QuizGame& game){
    //=== SETUP ===
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    //Banner 
    std::cout << "\n" << ColorTheme::BOLD << ColorTheme::CYAN << "⚡ QUICK ATTACK MODE"
              << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::YELLOW << "You have 5 Minutes! Wrong Answers Cost 15 seconds!"
              << ColorTheme::RESET << "\n" << std::endl;
    
    //Start the 5 Minute countdown
    game.globalTimer.start();

    //=== MAIN LOOP ===
    int questionsAnswered = 0;

    while(!game.globalTimer.is_time_up() && game.currentQuestionIndex < static_cast<int>(game.filteredQuestions.size()))
    {
            Question* currentQuestion = game.filteredQuestions[game.currentQuestionIndex];

            //=== DISPLAY REMAINING TIME ===
            int remaining = game.globalTimer.get_remaining_seconds();
            int minutes = remaining / 60;
            int seconds = remaining % 60;

            std::cout << ColorTheme::BOLD << ColorTheme::YELLOW 
                      << "⏱️ Time Remaining: " << minutes << "m " << seconds
                      << "s" << ColorTheme::RESET << std::endl;
            
            //Question Header
            ColorTheme::print_question_header(
                    game.currentQuestionIndex + 1,
                    game.filteredQuestions.size()
            );

            //Display Question
            currentQuestion->display();

            //=== GET USER ANSWER ===
            std::string userAnswer;
            bool validInput = false;

            while (!validInput){
                std::cout << ColorTheme::CYAN << "Your Answer: "
                          << ColorTheme::RESET; 
                    std::getline(std::cin, userAnswer);

                //Check if MC or TF
                MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(currentQuestion);

                if (mcq){
                    //Multiple choice, A B C D
                    if (userAnswer.length() == 1 && (userAnswer[0] == 'A' || 
                    userAnswer[0] == 'a' || userAnswer[0] == 'B' ||
                    userAnswer[0] == 'b' || userAnswer[0] == 'C' ||
                    userAnswer[0] == 'c' || userAnswer[0] == 'D' ||
                    userAnswer[0] == 'd')){
                        validInput = true;
                    }
                }else{
                    //True/False quesitons
                    std::string lowerAnswer = userAnswer;
                    std::transform(lowerAnswer.begin(), lowerAnswer.end(),
                                        lowerAnswer.begin(), ::tolower);
                    if(lowerAnswer == "true" || lowerAnswer == "false"){
                        validInput = true;
                    }
                }
                if (!validInput){
                    std::cout << ColorTheme::RED << "❌ Invalid Input!"
                              << (mcq ? "Enter A, B, C, D." : "Enter 'true' or 'false'.")
                              <<ColorTheme::RESET << std::endl;
                }
            }

            //=== Check Answer ===
            bool correct = currentQuestion->checkAnswer(userAnswer);

            if (correct){
                ColorTheme::print_correct_message(currentQuestion->get_points());
                game.earnedScore += currentQuestion->get_points();
                game.correctCount++;
                game.currentStreak++;

                if (game.currentStreak > game.bestStreak){
                    game.bestStreak = game.currentStreak;
                }
            }else{
                ColorTheme::print_wrong_message();
                game.currentStreak = 0;

                //Penalty 15 seconds
                game.globalTimer.apply_penalty(15);
                std::cout << ColorTheme::RED << ColorTheme::BOLD
                          << "⏱️ -15 SECONDS PENALTY!"
                          << ColorTheme::RESET << std::endl;
            }
            questionsAnswered++;
            game.currentQuestionIndex++;

            std::cout << std::endl;
    }

    //=== Game Over ===
    game.globalTimer.stop();

    std::cout << "\n" << ColorTheme::BOLD << ColorTheme::RED << "⏱️ TIME'S UP!"
              << ColorTheme::RESET << "\n" << std::endl;
    
    std::cout << ColorTheme::YELLOW << "Questions Answered: " << questionsAnswered
              << ColorTheme::RESET << std::endl;

    //=== Display Results ===
    game.display_results();
    game.display_achievements();
}


//============================
//RUN SURVIVAL - 3 Lives Mode
//============================
//Start with 3 lives 
//Wrong answer costs 1 life
//Correct answers keeps it
//Game over when lives equals to 0
//No timer pressure just survive
void GameModes::run_survival(QuizGame& game){
    //=== SETUP ===
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    //Limit Questions to what user configures
    if (game.filteredQuestions.size() > static_cast<size_t>(game.totalQuestionsToAsk)){
        game.filteredQuestions.resize(game.totalQuestionsToAsk);
    }

    //Banner
    std::cout << "\n" << ColorTheme::BOLD << ColorTheme::RED << "💀 SURVIVAL MODE 💀"
                      << ColorTheme::RESET << std::endl;
    std::cout << ColorTheme::YELLOW << "You have 3 Lives. Don't lose them all!"
              << ColorTheme::RESET << "\n" << std::endl;

    //Reset lives to 3
    game.lives.reset();

    //=== MAIN LOOP ===
    while (!game.lives.is_game_over() && game.currentQuestionIndex < static_cast<int>(game.filteredQuestions.size()))
    {
        Question* currentQuestion = game.filteredQuestions[game.currentQuestionIndex];

        //=== DISPLAY LIVES ===
        game.lives.display();
        std::cout << std::endl;

        //Question Header
        ColorTheme::print_question_header(
            game.currentQuestionIndex + 1,
            game.filteredQuestions.size()
        );

        //Display Question
        currentQuestion->display();

        //=== GET USER ANSWER ===
        std::string userAnswer;
        bool validInput = false;

        while (!validInput)
        {
            std::cout << ColorTheme::CYAN << "Your Answer: " << ColorTheme::RESET;
            std::getline(std::cin, userAnswer);

            //Check if MC or TF
            MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(currentQuestion);
            if (mcq){
                //Multiple Choice: A, B, C or D
                if (userAnswer.length() == 1 && (userAnswer[0] == 'A' || userAnswer[0] == 'a' ||
                                                userAnswer[0] == 'B' || userAnswer[0] == 'b' ||
                                                userAnswer[0] == 'C' || userAnswer[0] == 'c' ||
                                                userAnswer[0] == 'D' || userAnswer[0] == 'd')){
                                                    validInput = true;
                                                }
            }else{
              //True/False
              std::string lowerAnswer = userAnswer;
              std::transform(lowerAnswer.begin(), lowerAnswer.end(),
                                lowerAnswer.begin(), ::tolower);
                    if(lowerAnswer == "true" || lowerAnswer == "false"){
                        validInput = true;
                    }  
            }

            if (!validInput){
                std::cout << ColorTheme::RED << "❌ Invalid Input!"
                << (mcq ? "Enter A, B, C or D." : "Enter 'true' or 'false'.")
                << ColorTheme::RESET << std::endl;
            }
        }

        //=== CHECK ANSWER ===
        bool correct = currentQuestion->checkAnswer(userAnswer);

        if (correct){
            ColorTheme::print_correct_message(currentQuestion->get_points());
            game.earnedScore += currentQuestion->get_points();
            game.correctCount++;
            game.currentStreak++;

            if (game.currentStreak > game.bestStreak){
                game.bestStreak = game.currentStreak;
            }
        }else{
            ColorTheme::print_wrong_message();
            game.currentStreak = 0;

            //LOSE A LIFE
            game.lives.lose_life();

            if (game.lives.get_remaining() > 0){
                std::cout << ColorTheme::RED << ColorTheme::BOLD << "💔 LIFE LOST!"
                    << game.lives.get_remaining() << " remaining!" << ColorTheme::RESET << std::endl;
            }
        }

        game.currentQuestionIndex++;

        std::cout << ColorTheme::DIM << "\nPress Enter to Continue... " << ColorTheme::RESET;
        std::cin.get();
        std::cout << "\n\n";
    }

    //=== GAME OVER CHECK ===
    if (game.lives.is_game_over()){
        std::cout << "\n" << ColorTheme::BOLD << ColorTheme::RED << "💀 GAME OVER - ALL LIVES LOST! 💀"
                  << ColorTheme::RESET << "\n" << std::endl;
    }else{
        std::cout << "\n" << ColorTheme::BOLD << ColorTheme::GREEN << "🎉 YOU SURVIVED! 🎉" 
            << ColorTheme::RESET << "\n" << std::endl;
    }

    //Display Results
    game.display_results();
    game.display_achievements();


}
