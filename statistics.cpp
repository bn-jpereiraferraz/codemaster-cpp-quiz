#include "statistics.h"
#include "QuizGame.h"
#include "ColorTheme.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>

//STATISTICS CLASS IMPLEMENTATION

//Constructor initializing everything to 0
Statistics::Statistics()
    : totalGamesPlayed(0),
      totalQuestionsAnswered(0),
      totalCorrectAnswers(0),
      totalPointsEarned(0),
      longestStreakEver(0){

    //initialize per mode arrays to zero
    for (int i = 0; i < 6; i++){
        gamesPlayedPerMode[i] = 0;
        correctPerMode[i] = 0;
        totalPerMode[i] = 0;
        highScorePerMode[i] = 0;
    }
    //Maps are empty by default!
}

//Record a completed game - updates all of the stats
void Statistics::record_game(Gamemode mode, int score, int correct, int total, int streak){
    //Update stats
    totalGamesPlayed++;
    totalQuestionsAnswered += total;  // Add total questions from this game
    totalCorrectAnswers += correct;
    totalPointsEarned += score;

    //Update longest streak if current run was better
    if (streak > longestStreakEver){
        longestStreakEver = streak;
    }

    //Update per mode stats
    int modeIndex = static_cast<int>(mode); //Convert enum to array index
    gamesPlayedPerMode[modeIndex]++;
    correctPerMode[modeIndex] += correct;
    totalPerMode[modeIndex] += total;

    //Update high score for current mode if higher
    if (score > highScorePerMode[modeIndex]){
        highScorePerMode[modeIndex] = score;
    }

    //Add to high scores list with current date
    ScoreEntry entry;
    entry.score = score;
    entry.correctCount = correct;
    entry.totalQuestions = total;

    //Get current date as a string 
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateStr[20];
    sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    entry.date = dateStr;

    highScores[modeIndex].push_back(entry);

    //Only Top 5 scores will be saved, descending organized
    std::sort(highScores[modeIndex].begin(), highScores[modeIndex].end(), 
                [](const ScoreEntry& a, const ScoreEntry& b){
                  return a.score > b.score;  
    });

    
    if (highScores[modeIndex].size() > 5){
        highScores[modeIndex].resize(5);
    }
}

void Statistics::record_category_performance(std::string category, bool correct){
    //Increment totla questions for this category
    categoryTotal[category]++;

    //If correct, icrement correct count for current category
    if (correct){
        categoryCorrect[category]++;
    }

    //Maps Automatically creates entriers if they don't exist
}

void Statistics::display_career_stats(){
    std::cout << "\n" << ColorTheme::CYAN 
    << "═══════════════════════════════════════════════" << ColorTheme::RESET << "\n";
    
    std::cout << ColorTheme::YELLOW << "           📊 CAREER STATISTICS 📊"
              << ColorTheme::RESET << "\n";
    
    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════" << ColorTheme::RESET << "\n\n";

    //Total Games played
    std::cout << ColorTheme::GREEN << "🎮 Total Games Played: " << ColorTheme::RESET
              << totalGamesPlayed << "\n";

    //Total Questions answered
    std::cout << ColorTheme::GREEN << "❓ Total Questions Answered: " << ColorTheme::RESET 
              << ColorTheme::RESET << totalQuestionsAnswered << "\n";
    
    //Total Correct Answers
    std::cout << ColorTheme::GREEN << "✅ Total Correct Answers: " << ColorTheme::RESET
            << ColorTheme::RESET << totalCorrectAnswers << "\n";

    //Accuracy calculation and Display
    if (totalCorrectAnswers > 0) {
        double accuracy = (static_cast<double>(totalCorrectAnswers) / totalQuestionsAnswered) * 100.0;
        std::cout << ColorTheme::GREEN << "🎯 Overall Accuracy: " << ColorTheme::RESET
                  << std::fixed << std::setprecision(1) << accuracy << "%\n";
    }

    //Total Points earned
    std::cout << ColorTheme::GREEN << "⭐ Total Points earned: " << ColorTheme::RESET
              << totalPointsEarned << "\n";

    //Longest streak 
    std::cout << ColorTheme::GREEN << "🔥 Longest Streak Ever: " << ColorTheme::RESET
              << longestStreakEver << "\n";

    std::cout << ColorTheme::GREEN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

void Statistics::display_mode_stats(Gamemode mode){
    int modeIndex = static_cast<int>(mode); //Enum conversion into array index

    //Mode names display
    std::string modeNames[] = {
        "CLASSIC", "QUICK ATTACK", "SURVIVAL",
        "MARATHON", "LIGHTNING", "PRACTICE"
    };

    std::cout << "\n" << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
    
    std::cout << ColorTheme::YELLOW << "      📊 " << modeNames[modeIndex] << " MODE STATS 📊"
              << ColorTheme::RESET << "\n";
    
    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n\n";

    //Quizes taken in the current Mode
    std::cout << ColorTheme::GREEN << "🎮 Games Played: " << ColorTheme::RESET
              << gamesPlayedPerMode[modeIndex] << "\n";
    
    //Questions Answered in the current Mode
    std::cout << ColorTheme::GREEN << "❓ Questions Answered: " << ColorTheme::RESET
              << totalPerMode[modeIndex] << "\n";

    //Correct Answers in Current Mode
    std::cout << ColorTheme::GREEN << "✅ Correct Answers: " << ColorTheme::RESET
              << correctPerMode[modeIndex] << "\n";

    //Accuracy calculation and display for current mode
    if (totalPerMode[modeIndex] > 0){
        double accuracy = (static_cast<double>(correctPerMode[modeIndex]) / totalPerMode[modeIndex]) * 100.0;

        std::cout << ColorTheme::GREEN << "🎯 Accuracy: " << ColorTheme::RESET
                  << std::fixed << std::setprecision(1) << accuracy << "%\n";
    }

    //High score in current Mode
    std::cout << ColorTheme::GREEN << "🏆 High Score: " << ColorTheme::RESET
              << highScorePerMode[modeIndex] << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

//Display stats by category
void Statistics::display_category_stats(){
    std::cout << "\n" << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
    
    std::cout << ColorTheme::YELLOW << "      📁 CATEGORY PERFORMANCE 📁" << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n\n";
    
    //Check if date of category already saved
    if (categoryTotal.empty()){
        std::cout << ColorTheme::DIM << "No category data. Play some games!\n" << ColorTheme::RESET;
        std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
                  << ColorTheme::RESET << "\n";
                return;
    }
    //Iterate through categories
    for (auto& pair : categoryTotal){
        std::string category = pair.first;
        int total = pair.second;
        int correct = categoryCorrect[category]; //get correct count (0 if not found)

        //accuracy calculation
        double accuracy = (static_cast<double>(correct) / total) * 100.0;

        //Display Category stats
        std::cout << ColorTheme::GREEN << "📁 " << category << ": " << ColorTheme::RESET;
        std::cout << correct << "/" << total << " ";
        std::cout << "(" << std::fixed << std::setprecision(1) << accuracy << "%)\n";
    }

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

//Display top 5 high scores for specific mode
void Statistics::display_high_scores(Gamemode mode) {
    int modeIndex = static_cast<int>(mode); //Enum convertion into an array

    //Mode names in Display

    std::string modeNames[] = {
        "CLASSIC", "QUICK ATTACK", "SURVIVAL",
        "MARATHON", "LIGHTNING", "PRACTICE"
    };

    std::cout << "\n" << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
    
    std::cout << ColorTheme::YELLOW << "   🏆 TOP 5 HIGH SCORES - " << modeNames[modeIndex] << " 🏆"
              << ColorTheme::RESET << "\n";

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n\n";

    //Check if any scores saved
    if (highScores[modeIndex].empty()){
        std::cout << ColorTheme::DIM << "No High Scores yet. Make some Quiz runs! In " << modeNames[modeIndex]
                  << " mode!\n" << ColorTheme::RESET;
        
        std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
                  << ColorTheme::RESET << "\n";
            return;
    }

    //Display each high score entry
    for(size_t i = 0; i < highScores[modeIndex].size(); i++)
    {
        ScoreEntry entry = highScores[modeIndex][i];

        //Rank number with medal emojis top 3 only
        std::cout << ColorTheme::YELLOW;
        if (i == 0) std::cout << "🥇 1.";
        else if (i == 1) std::cout << "🥈 2.";
        else if (i == 2) std::cout << "🥉 3.";
        else std::cout << (i + 1) << ". ";
        std::cout << ColorTheme::RESET;

        //Score and accuracy
        std::cout << ColorTheme::GREEN << entry.score << " pts" << ColorTheme::RESET << " | ";
        std::cout << entry.correctCount << "/" << entry.totalQuestions << " | ";
        std::cout << ColorTheme::DIM << entry.date << ColorTheme::RESET << "\n"; 
    }

    std::cout << ColorTheme::CYAN << "═══════════════════════════════════════════════"
              << ColorTheme::RESET << "\n";
}

//Save statistics to file for persistence
bool Statistics::save_to_file(std::string filename){
    std::ofstream outFile(filename);

    //Check if file opened successfully
    if (!outFile.is_open()){
        return false; //Failed to open
    }

    //Save career stats (one per line)
    outFile << totalGamesPlayed << "\n";
    outFile << totalQuestionsAnswered << "\n";
    outFile << totalCorrectAnswers << "\n";
    outFile << totalPointsEarned << "\n";
    outFile << longestStreakEver << "\n";

    //Save per mode array (6 values each, space-separated)
    for (int i = 0; i < 6; i++){
        outFile << gamesPlayedPerMode[i] << " ";
    }
    outFile << "\n";

    for (int i = 0; i < 6; i++)
    {
        outFile << correctPerMode[i] << " ";
    }
    outFile << "\n";

    for (int i = 0; i < 6; i++){
        outFile << totalPerMode[i] << " "; 
    }
    outFile << "\n";

    for (int i = 0; i < 6; i++){
        outFile << highScorePerMode[i] << " ";
    }
    outFile << "\n";

    //Save Category Performance (count first, then pairs)
    outFile << categoryTotal.size() << "\n"; //How many categories
    for (auto& pair : categoryTotal){
        outFile << pair.first << "|"; //Category name;
        outFile << pair.second << "|"; //Total questions;
        outFile << categoryCorrect[pair.first] << "\n"; //Correct answers;
    }

    //Save high scores for each mode
    for (int i = 0; i<  6; i++){
        outFile << highScores[i].size() << "\n"; //How many scores for this mode
        for (ScoreEntry& entry : highScores[i]){
            outFile << entry.score << "|";
            outFile << entry.correctCount << "|";
            outFile << entry.totalQuestions << "|";
            outFile << entry.date << "|";
        }
    }
    outFile.close();
    return true; //Success;
}

//Load Statistics from File
bool Statistics::load_from_file(std::string filename){

    std::ifstream inFile(filename);

    //Check if file opened successfully
    if (!inFile.is_open()){
        return false; //File doesn't exist or can't be opened
    }

    //Load career stats
    inFile >> totalGamesPlayed;
    inFile >> totalQuestionsAnswered;
    inFile >> totalCorrectAnswers;
    inFile >> totalPointsEarned;
    inFile >> longestStreakEver;

    //Load per-mode Arrays
    for (int i = 0; i < 6; i++){
        inFile >> gamesPlayedPerMode[i];
    }

    for (int i = 0; i < 6; i++){
        inFile >> correctPerMode[i];
    }

    for (int i = 0; i < 6; i++){
        inFile >> totalPerMode[i];
    }

    for (int i = 0; i < 6; i++){
        inFile >> highScorePerMode[i];
    }

    //Load Category Performance
    int categoryCount;
    inFile >> categoryCount;
    inFile.ignore(); //Skip new line after count;

    for (int i = 0; i < categoryCount; i++){
        std::string line;
        std::getline(inFile, line);

        //Parse: category|total|correct
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        std::string category = line.substr(0, pos1);
        int total = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        int correct = std::stoi(line.substr(pos2 + 1));

        categoryTotal[category] = total;
        categoryCorrect[category] = correct;
    }

    //Load high scores for each mode
    for (int i = 0; i < 6; i++){
        int scoreCount; 
        inFile >> scoreCount;
        inFile.ignore(); //Skip newline;

        highScores[i].clear(); //Clear existing scores

        for (int j = 0; j < scoreCount; j++){
            std::string line;
            std::getline(inFile, line);

            //Parse: score|correctCount|totalQuetions|date
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            ScoreEntry entry;
            entry.score = std::stoi(line.substr(0, pos1));
            entry.correctCount = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            entry.totalQuestions = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            entry.date = line.substr(pos3 + 1);

            highScores[i].push_back(entry);
        }
    }

    inFile.close();
    return true; //Success
}

