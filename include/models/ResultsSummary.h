#ifndef RESULTSSUMMARY_H
#define RESULTSSUMMARY_H
#include <string>

struct ResultsSummary{
    int totalQuestions;     //questions answered
    int correctAnswers;     //Correct count
    int wrongAnswers;       //Wrong count
    int score;              //Final score
    int maxScore;           //Maximum possible score
    std::string grade;      //Letter grade
    int timeSpent;          //Total time in seconds
    int bestStreak;         //Best correct streak
    bool perfectScore;      //All Correct;
    bool newHighScore;      //Beat previoud best

    ResultsSummary()
        :totalQuestions(0), correctAnswers(0), wrongAnswers(0), score(0), maxScore(0),
        grade("N/A"), timeSpent(0), bestStreak(0), perfectScore(false), newHighScore(false){}

    //Calculate accuracy %
    double get_accuracy()const{
        if (totalQuestions == 0) return 0.0;
        return (correctAnswers * 100.0) / totalQuestions;
    }

    //Calculate score %
    double get_score_percentage()const{
        if (maxScore == 0) return 0.0;
        return (score * 100.0) / maxScore;
    }
};
#endif // RESULTSSUMMARY_H
