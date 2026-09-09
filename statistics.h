#ifndef STATISTICS_H
#define STATISTICS_H
#include <map>
#include <string>
#include <vector>
#include "Gamemode.h"

class Statistics{
private:
    //Carrer stats
    int totalGamesPlayed;
    int totalQuestionsAnswered;
    int totalCorrectAnswers;
    int totalPointsEarned;
    int longestStreakEver;

    //Stats per Mode arrays indexed by game Mode
    int gamesPlayedPerMode[6];
    int correctPerMode[6];
    int totalPerMode[6];
    int highScorePerMode[6];

    //Stats per Category
    std::map<std::string, int> categoryCorrect;
    std::map<std::string, int> categoryTotal;

    //High Scores
    struct ScoreEntry{
        int score;
        int correctCount;
        int totalQuestions;
        std::string date;
    };
    std::vector<ScoreEntry> highScores[6];
public:
    Statistics(); //Constructor default

    //Update Methods
    void record_game(Gamemode mode, int score, int correct, int total, int streak);
    void record_category_performance(std::string category, bool correct);

    //Save/Load mechanism
    bool save_to_file(std::string filename);
    bool load_from_file(std::string filename);

    //Display
    void display_career_stats();
    void display_mode_stats(Gamemode mode);
    void display_category_stats();
    void display_high_scores(Gamemode mode);

};

#endif