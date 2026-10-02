#ifndef LIVESTATS_H
#define LIVESTATS_H

struct LiveStats{
    int currentQuestion;    //Which question
    int totalQuestions;     //Total questions in quiz
    int correctAnswers;     //Running count of correct
    int wrongAnswers;       //Running count of wrong
    int currentStreak;      //Current correct streak
    int bestStreak;         //Best streak this session
    int remainingLives;     //Lives left
    int score;              //Current score

    LiveStats()
        :currentQuestion(0), totalQuestions(0), correctAnswers(0), wrongAnswers(0), 
        currentStreak(0), bestStreak(0), remainingLives(0), score(0){}

    //Calculate accuracy %
    double get_accuracy()const{
        int total = correctAnswers + wrongAnswers;
        if (total == 0) return 0.0;
        return (correctAnswers * 100.0) / total;
    }
};



#endif // LIVESTATS_H
