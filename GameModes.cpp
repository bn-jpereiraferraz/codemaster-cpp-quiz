#include "GameModes.h"
#include "QuizGame.h"
#include "ColorTheme.h"
#include "Timer.h" 
#include "GlobalTimer.h"
#include "Lives.h"
#include "MultipleChoiceQuestion.h"
#include "AsciiArt.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

void GameModes::run_classic(QuizGame& game){
    // Display banner
    AsciiArt::display_classic_banner();
    std::cout << std::endl;

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

    // Show actual question count being used
    std::cout << ColorTheme::CYAN << "📝 Using " << game.filteredQuestions.size()
              << " questions for this mode" << ColorTheme::RESET << std::endl;

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
        q->display_boxed();

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

    // Check if user completed enough to show full results
    if (game.currentQuestionIndex < 3) {
        // Quit too early
        std::cout << "\n" << ColorTheme::YELLOW
                  << "📖 Quiz ended early. Come back anytime to continue learning!"
                  << ColorTheme::RESET << std::endl;
        if (game.correctCount > 0) {
            std::cout << ColorTheme::GREEN
                      << "   " << game.correctCount << " correct so far!"
                      << ColorTheme::RESET << std::endl;
        }
    } else {
        // Display final results
        game.display_results();
        game.display_achievements();
    }
}

//=======================================
//RUN QUICK ATTACK 5 Minute Time Attack
//=======================================
void GameModes::run_quick_attack(QuizGame& game){
    //=== SETUP ===
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    // Limit to user's chosen question count
    if (game.filteredQuestions.size() > static_cast<size_t>(game.totalQuestionsToAsk)) {
        game.filteredQuestions.resize(game.totalQuestionsToAsk);
    }

    // Show actual question count being used
    std::cout << ColorTheme::CYAN << "📝 Using " << game.filteredQuestions.size()
              << " questions for this mode" << ColorTheme::RESET << std::endl;

    // Calculate total possible score
    game.totalScore = 0;
    for (Question* q : game.filteredQuestions) {
        game.totalScore += q->get_points();
    }

    //Banner
    AsciiArt::display_quick_attack_banner();
    std::cout << std::endl;
    
    //Start the 5 Minute countdown
    game.globalTimer.start();

    //=== MAIN LOOP ===
    int questionsAnswered = 0;

    while(!game.globalTimer.is_time_up() && game.currentQuestionIndex < static_cast<int>(game.filteredQuestions.size()))
    {
            Question* currentQuestion = game.filteredQuestions[game.currentQuestionIndex];

            //=== DISPLAY REMAINING TIME ===
            game.globalTimer.display_progress_bar();
            std::cout << std::endl;
            
            //Question Header
            ColorTheme::print_question_header(
                    game.currentQuestionIndex + 1,
                    game.filteredQuestions.size()
            );

            //Display Question
            currentQuestion->display_boxed();

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

    // Check if it was a good run or early failure
    if (questionsAnswered >= 10) {
        // Decent attempt - show full results
        game.display_results();
        game.display_achievements();
    } else {
        // Too few questions - encouraging message
        std::cout << "\n" << ColorTheme::CYAN
                  << "⚡ Quick Attack is tough! Try again for a better score!"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::GREEN
                  << "   " << game.correctCount << " correct out of " << questionsAnswered
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::DIM
                  << "   Tip: Answer faster to avoid penalties!"
                  << ColorTheme::RESET << std::endl;
    }
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

    // Show actual question count being used
    std::cout << ColorTheme::CYAN << "📝 Using " << game.filteredQuestions.size()
              << " questions for this mode" << ColorTheme::RESET << std::endl;

    // Calculate total possible score
    game.totalScore = 0;
    for (Question* q : game.filteredQuestions) {
        game.totalScore += q->get_points();
    }

    //Banner
    AsciiArt::display_survival_banner();
    std::cout << std::endl;

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
        currentQuestion->display_boxed();

        //=== START TIMER IF ENABLED ===
        Timer questionTimer(game.questionTimeLimit);
        if (game.timerEnabled) {
            questionTimer.start();
            std::cout << ColorTheme::YELLOW << "\n⏱️  Timer: " << game.questionTimeLimit
                      << " seconds" << ColorTheme::RESET << std::endl;
        }

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

        //=== STOP TIMER IF ENABLED ===
        int secondsUsed = 0;
        if (game.timerEnabled) {
            questionTimer.stop();
            secondsUsed = questionTimer.get_elapsed_seconds();

            // Check if time ran out
            if (secondsUsed >= game.questionTimeLimit) {
                std::cout << ColorTheme::RED << ColorTheme::BOLD
                          << "\n⏰ TIME'S UP!" << ColorTheme::RESET << std::endl;
                // Treat as wrong answer - lose a life
                game.lives.lose_life();
                game.currentStreak = 0;

                if (game.lives.get_remaining() > 0) {
                    std::cout << ColorTheme::RED << ColorTheme::BOLD << "💔 LIFE LOST! "
                              << game.lives.get_remaining() << " remaining!" << ColorTheme::RESET << std::endl;
                }

                game.currentQuestionIndex++;
                std::cout << ColorTheme::DIM << "\nPress Enter to Continue... " << ColorTheme::RESET;
                std::cin.get();
                std::cout << "\n\n";
                continue; // Skip to next question
            }
        }

        //=== CHECK ANSWER ===
        bool correct = currentQuestion->checkAnswer(userAnswer);

        if (correct){
            // Calculate bonus points for speed (if timer enabled)
            int basePoints = currentQuestion->get_points();
            int bonusPoints = 0;
            if (game.timerEnabled) {
                bonusPoints = game.calculate_bonus_points(basePoints, secondsUsed, game.questionTimeLimit);
                game.totalBonusPoints += bonusPoints;
            }

            ColorTheme::print_correct_message(basePoints + bonusPoints);
            game.earnedScore += basePoints + bonusPoints;
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

        // Show encouraging message instead of full results
        std::cout << ColorTheme::YELLOW
                  << "\n📊 You answered " << game.currentQuestionIndex << " questions"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::GREEN
                  << "   " << game.correctCount << " correct"
                  << ColorTheme::RESET << std::endl;

        std::cout << "\n" << ColorTheme::CYAN
                  << "💪 Don't give up! Every attempt makes you stronger!"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::DIM
                  << "   Tip: Review the questions you missed and try again!"
                  << ColorTheme::RESET << std::endl;
    }else{
        std::cout << "\n" << ColorTheme::BOLD << ColorTheme::GREEN << "🎉 YOU SURVIVED! 🎉"
            << ColorTheme::RESET << "\n" << std::endl;

        // Full results for successful completion
        game.display_results();
        game.display_achievements();
    }


}

//================================
//RUN MARATHON - All 300 Questions
//================================
//Rules:
//Answer ALL 300 questions
//Track total session time
//no Pressure per question
//N lives system
//Pure endurance test
void GameModes::run_marathon(QuizGame& game){
    //=== SETUP ===
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    // Note: Marathon is fixed at 300, but limit anyway in case fewer questions available
    if (game.filteredQuestions.size() > static_cast<size_t>(game.totalQuestionsToAsk)) {
        game.filteredQuestions.resize(game.totalQuestionsToAsk);
    }

    //Banner
    AsciiArt::display_marathon_banner();
    std::cout << std::endl;

    //Start a timer to track total session time
    Timer marathonTimer(0); //No Time limit, just track
    marathonTimer.start();

    //Calculate total possible score
    game.totalScore = 0;
    for (Question* q : game.filteredQuestions){
        game.totalScore += q->get_points();
    }

    std::cout << ColorTheme::DIM << "Press Enter to begin the Marathon" <<ColorTheme::RESET;
    std::cin.get();

    //MAIN LOOP
    while(game.currentQuestionIndex < static_cast<int>(game.filteredQuestions.size()))
    {
        Question* currentQuestion = game.filteredQuestions[game.currentQuestionIndex];

        //Clear screen effect
        std::cout << "\n\n\n";

        //Question Header
        ColorTheme::print_question_header(
            game.currentQuestionIndex + 1,
            game.filteredQuestions.size()
        );
        ColorTheme::print_progress_bar(
            game.currentQuestionIndex + 1,
            game.filteredQuestions.size()
        );

        //Display Question
        currentQuestion->display_boxed();

        //=== START TIMER IF ENABLED ===
        Timer questionTimer(game.questionTimeLimit);
        if (game.timerEnabled) {
            questionTimer.start();
            std::cout << ColorTheme::YELLOW << "\n⏱️  Timer: " << game.questionTimeLimit
                      << " seconds" << ColorTheme::RESET << std::endl;
        }

        //=== GET USER ANSWER ===
        std::string userAnswer;
        bool validInput = false;

        while(!validInput){
            std::cout << ColorTheme::CYAN << "Your Answer: " << ColorTheme::RESET;
            std::getline(std::cin, userAnswer);

            //Check if MC or TF
            MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(currentQuestion);
            if (mcq){
                if (userAnswer.length() == 1 &&(userAnswer[0] == 'A' || userAnswer[0] == 'a' ||
                                                userAnswer[0] == 'B' || userAnswer[0] == 'b' ||
                                                userAnswer[0] == 'C' || userAnswer[0] == 'c' ||
                                                userAnswer[0] == 'D' || userAnswer[0] == 'd' )){
                            validInput = true;                                
                    }
            }else{
                //True/False
                std::string lowerAnswer = userAnswer;
                std::transform(lowerAnswer.begin(), lowerAnswer.end(),
                                lowerAnswer.begin(), ::tolower);
                if (lowerAnswer == "true" || lowerAnswer == "false"){
                    validInput = true;
                }
            }

            if (!validInput){
                std::cout << ColorTheme::RED << "❌ Invalid Input! "
                          << (mcq ? "Enter A, B, C or D." : "Enter 'true' or 'false'.")
                          << ColorTheme::RESET << std::endl;
            }
        }

        //=== STOP TIMER IF ENABLED ===
        int secondsUsed = 0;
        if (game.timerEnabled) {
            questionTimer.stop();
            secondsUsed = questionTimer.get_elapsed_seconds();

            // Check if time ran out (treat as wrong answer in Marathon)
            if (secondsUsed >= game.questionTimeLimit) {
                std::cout << ColorTheme::RED << ColorTheme::BOLD
                          << "\n⏰ TIME'S UP!" << ColorTheme::RESET << std::endl;
                ColorTheme::print_wrong_message();
                game.currentStreak = 0;
                game.currentQuestionIndex++;
                std::cout << ColorTheme::DIM << "\nPress Enter to Continue... " << ColorTheme::RESET;
                std::cin.get();
                continue; // Skip to next question
            }
        }

        //=== CHECK ANSWER ===
        bool correct = currentQuestion->checkAnswer(userAnswer);

        if (correct){
            // Calculate bonus points for speed (if timer enabled)
            int basePoints = currentQuestion->get_points();
            int bonusPoints = 0;
            if (game.timerEnabled) {
                bonusPoints = game.calculate_bonus_points(basePoints, secondsUsed, game.questionTimeLimit);
                game.totalBonusPoints += bonusPoints;
            }

            ColorTheme::print_correct_message(basePoints + bonusPoints);
            game.earnedScore += basePoints + bonusPoints;
            game.correctCount++;
            game.currentStreak++;

            if (game.currentStreak > game.bestStreak){
                game.bestStreak = game.currentStreak;
            }

            //Streak Milestones
            if (game.currentStreak == 10){
                std::cout << ColorTheme::YELLOW << "🔥 10-STREAK! Amazing"
                          << ColorTheme::RESET << std::endl;
            }else if (game.currentStreak == 25){
                std::cout << ColorTheme::YELLOW << "🔥🔥 25-STREAK! Incredible!"
                          << ColorTheme::RESET << std::endl;
            }else if(game.currentStreak == 50){
                std::cout << ColorTheme::YELLOW << "🔥🔥🔥 50-STREAK! LEGENDARY!"
                          << ColorTheme::RESET << std::endl;
            }

        }else{
                ColorTheme::print_wrong_message();
                game.currentStreak = 0;
            }
        game.currentQuestionIndex++;

        //Live stats every 10th question
        if(game.currentQuestionIndex % 10 == 0 && game.currentQuestionIndex <static_cast<int>(game.filteredQuestions.size()))
        {
            game.display_live_stats(game.currentQuestionIndex, game.filteredQuestions.size());

            std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
            std::cin.get();
        }else{
            //Small Pause between questions
            std::cout << ColorTheme::DIM << "\nPress Enter for next question..." << ColorTheme::RESET;
            std::cin.get();
        } 
    }
    //=== MARATHON COMPLETE ===
    marathonTimer.stop();
    int totalSeconds = marathonTimer.get_elapsed_seconds();
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    std::cout << "\n" << ColorTheme::BOLD << ColorTheme::MAGENTA 
              << "🏁 MARATHON COMPLETE! 🏁" << ColorTheme::RESET << "\n" << std::endl;

    std::cout << ColorTheme::YELLOW << "Total Time: " << hours << "h " << minutes << "m " << seconds << "s"
              << ColorTheme::RESET << std::endl;

    //Display Results
    game.display_results();
    game.display_achievements();
}

//=========================================
//RUN LIGHTNING - 10 Seconds per Question
//=========================================
//Rules:
//-Strict 10 second timer per question
//-Timer auto-fails if you run out of time
//-No Lifelines(too fast-paced)
//-High pressure - quick thinking required!
void GameModes::run_lightning(QuizGame& game){
    //=== SETUP ===
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    //Limit Questions to what user configured
    if(game.filteredQuestions.size() > static_cast<size_t>(game.totalQuestionsToAsk)){
        game.filteredQuestions.resize(game.totalQuestionsToAsk);
    }

    // Show actual question count being used
    std::cout << ColorTheme::CYAN << "📝 Using " << game.filteredQuestions.size()
              << " questions for this mode" << ColorTheme::RESET << std::endl;

    //Calculate total score
    game.totalScore = 0;
    for (Question* q : game.filteredQuestions){
        game.totalScore += q->get_points();
    }

    //Banner
    AsciiArt::display_lightning_banner();
    std::cout << std::endl;
    std::cout << ColorTheme::DIM << "Press Enter to begin..." << ColorTheme::RESET;
    std::cin.get();

    //=== MAIN LOOP ===

    const int LIGHTNING_TIME_LIMIT = 10; //ten seconds

    while(game.currentQuestionIndex < static_cast<int>(game.filteredQuestions.size()))
    {
        Question* currentQuestion = game.filteredQuestions[game.currentQuestionIndex];

        //Clear screen effect
        std::cout << "\n\n\n";

        //Question Header
        ColorTheme::print_question_header(
            game.currentQuestionIndex + 1,
            game.filteredQuestions.size()
        );

        //Display Question
        currentQuestion->display_boxed();

        //=== START STRICT TIMER ===
        Timer questionTimer(LIGHTNING_TIME_LIMIT);
        questionTimer.start();

        std::cout << ColorTheme::RED << ColorTheme::BOLD << "\n⚡ 10 SECONDS - GO!"
                  << ColorTheme::RESET << std::endl;

        // Note: Can't show animated timer bar because terminal input blocks
        // The timer DOES work - you'll get "TIME'S UP!" if you take too long

        //GET USER ANSWER
        std::string userAnswer;
        bool validInput = false;
        bool timedOut = false;

        while(!validInput && !timedOut){
            //Check if time's up
            if (questionTimer.is_time_up()){
                timedOut = true;
                break;
            }

            std::cout << ColorTheme::CYAN << "Your Answer: " << ColorTheme::RESET;
            std::getline(std::cin, userAnswer);

            //Check if MC or TF
            MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*> (currentQuestion);

            if (mcq){
                //MC: A.B.C OR D
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

            if (!validInput && !timedOut){
                std::cout << ColorTheme::RED << "❌ Invalid! "
                          << (mcq ? "A, B, C or D!" : "true/false!")
                          <<ColorTheme::RESET << std::endl;
            }
        }

        questionTimer.stop();
        //=== CHECK ANSWER OR TIME OUT ===
        if (timedOut){
            //Time Ran out - count as wrong
            std::cout << ColorTheme::RED << ColorTheme::BOLD << "\n⏰ TIME'S UP! TOO SLOW!"
                      << ColorTheme::RESET << std::endl;
            game.currentStreak = 0;
        }else{
            //Got answer in time
            bool correct = currentQuestion->checkAnswer(userAnswer);

            if (correct){
                ColorTheme::print_correct_message(currentQuestion->get_points());
                game.earnedScore += currentQuestion->get_points();
                game.correctCount++;
                game.currentStreak++;

                if (game.currentStreak > game.bestStreak){
                    game.bestStreak = game.currentStreak;
                }

                //Show time used
                int secondsUsed = questionTimer.get_elapsed_seconds();
                std::cout << ColorTheme::GREEN << "⚡ Answered in: " << secondsUsed << " seconds!"
                          << ColorTheme::RESET << std::endl;
            }else{
                ColorTheme::print_wrong_message();
                game.currentStreak = 0;
            }
        }
        game.currentQuestionIndex++;

        //Small Pause (shorter than other modes)
        std::cout << ColorTheme::DIM << "\nPress Enter..." << ColorTheme::RESET;
        std::cin.get();
    }
    //=== LIGHTNING COMPLETE ===
    std::cout << "\n" << ColorTheme::BOLD << ColorTheme::YELLOW << "⚡ LIGHTNING ROUND COMPLETE! ⚡"
              << ColorTheme::RESET << "\n" << std::endl;

    // Check performance - Lightning is tough!
    int questionsAnswered = game.currentQuestionIndex;
    double successRate = (questionsAnswered > 0) ?
                        ((double)game.correctCount / questionsAnswered * 100.0) : 0.0;

    if (questionsAnswered < 5 || successRate < 30.0) {
        // Too few answered or too many timeouts - encouraging message
        std::cout << "\n" << ColorTheme::RED
                  << "⚡ Lightning Round is INTENSE! Keep practicing!"
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::YELLOW
                  << "   Questions answered: " << questionsAnswered
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::GREEN
                  << "   Correct: " << game.correctCount
                  << ColorTheme::RESET << std::endl;
        std::cout << ColorTheme::DIM
                  << "   Tip: 10 seconds goes fast - trust your instincts!"
                  << ColorTheme::RESET << std::endl;
    } else {
        // Decent performance - show full results
        game.display_results();
        game.display_achievements();
    }
}

//========================================
//RUN PRACTICE - No pressure Learning Mode
//========================================
//RULES:
//-No Timer(take all the time you need)
//-No Lives or penalties
//-Shows CORRECT ANSWER after each question(learning mode!)
//-Perfect for studying and learning C++
void GameModes::run_practice(QuizGame& game){
    //=== SETUP ===
    game.filter_by_difficulty(game.selectedDifficulty);
    game.shuffle_questions();

    //Limit questions to what user configured
    if (game.filteredQuestions.size() > static_cast<size_t>(game.totalQuestionsToAsk)){
        game.filteredQuestions.resize(game.totalQuestionsToAsk);
    }

    // Show actual question count being used
    std::cout << ColorTheme::CYAN << "📝 Using " << game.filteredQuestions.size()
              << " questions for this mode" << ColorTheme::RESET << std::endl;

    //Calculate total score
    game.totalScore = 0;
    for (Question* q : game.filteredQuestions){
        game.totalScore += q->get_points();
    }

    //Banner
    AsciiArt::display_practice_banner();
    std::cout << std::endl;

    std::cout << ColorTheme::DIM << "Press Enter to begin..." << ColorTheme::RESET;
    std::cin.get();

    //=== MAIN LOOP ===
    while(game.currentQuestionIndex < static_cast<int>(game.filteredQuestions.size()))
    {
        Question* currentQuestion = game.filteredQuestions[game.currentQuestionIndex];

        //Clear Scree effect
        std::cout << "\n\n\n";

        //Question Header
        ColorTheme::print_question_header(
            game.currentQuestionIndex + 1,
            game.filteredQuestions.size()
        );
        ColorTheme::print_progress_bar(
            game.currentQuestionIndex + 1,
            game.filteredQuestions.size()
        );

        //Display Question
        currentQuestion->display_boxed();

        //=== GET USER ANSWER ===
        std::string userAnswer;
        bool validInput = false;

        while(!validInput){
            std::cout << ColorTheme::CYAN << "Your Answer: " << ColorTheme::RESET;
            std::getline(std::cin, userAnswer);

            //Check if MC or TF
            MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(currentQuestion);
            if (mcq){
                if (userAnswer.length() == 1 && (userAnswer[0] == 'A' || userAnswer[0] == 'a' ||
                                                 userAnswer[0] == 'B' || userAnswer[0] == 'b' ||
                                                 userAnswer[0] == 'C' || userAnswer[0] == 'c' ||
                                                 userAnswer[0] == 'D' || userAnswer[0] == 'd')){
                                        validInput = true;
                     }
            }else{
                //True / False
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

            //=== SHOW CORRECT ANSWER ===
            std::cout << "\n" << ColorTheme::YELLOW << ColorTheme::BOLD << "📖 Correct Answer: ";

            //Display the correct answer based on question type
            MultipleChoiceQuestion* mcq = dynamic_cast<MultipleChoiceQuestion*>(currentQuestion);

            if (mcq){
                //FOR MC SHOWS CORRECT LETTER
                std::cout << ColorTheme::GREEN << mcq->get_correct_answer() << ColorTheme::RESET << std::endl;
            }else{
                //For true or false we show true or false;
                if (currentQuestion->checkAnswer("true")){
                    std::cout << ColorTheme::GREEN << "True" << ColorTheme::RESET << std::endl;
                }else{
                    std::cout << ColorTheme::GREEN << "False" << ColorTheme::RESET << std::endl;
                }
            }
        }

        game.currentQuestionIndex++;
        //Longer pause in Practice mode
        std::cout << ColorTheme::DIM << "\nPress Enter to continue..." << ColorTheme::RESET;
        std::cin.get();
    }
    //=== PRACTICE MODE COMPLETE
    std::cout << "\n" << ColorTheme::BOLD << ColorTheme::CYAN << "📚 PRACTICE SESSION COMPLETE! 📚"
                    << ColorTheme::RESET << std::endl;

    //Display Results
    game.display_results();
    game.display_achievements();    
}
