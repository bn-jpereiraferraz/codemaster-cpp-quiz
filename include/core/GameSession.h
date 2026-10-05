#ifndef GAMESESSION_H
#define GAMESESSION_H

#include "models/ResultsSummary.h"

class GameSession {
private:
    int earnedScore;
    int totalScore;
    int correctCount;
    int wrongCount;
    int currentStreak;
    int bestStreak;
    int totalBonusPoints;
    int currentQuestionIndex;
    int currentHintLevel;

public:
    GameSession();

    // Answer processing
    void record_correct_answer(int points, int bonusPoints = 0);
    void record_wrong_answer();
    void reset_streak();
    void update_best_streak();

    // Hint tracking
    void increment_hint_level();
    void reset_hint_level();
    int get_hint_level() const;

    // Progress tracking
    void set_current_question_index(int index);
    int get_current_question_index() const;
    void advance_question();

    // Score management
    void set_total_score(int score);
    void set_earned_score(int score);       // For save/load
    void set_correct_count(int count);      // For save/load
    void set_current_streak(int streak);    // For save/load
    void set_best_streak(int streak);       // For save/load
    void set_total_bonus_points(int points);// For save/load

    int get_earned_score() const;
    int get_total_score() const;
    int get_correct_count() const;
    int get_wrong_count() const;
    int get_current_streak() const;
    int get_best_streak() const;
    int get_total_bonus_points() const;

    // Session summary
    ResultsSummary get_summary(size_t totalQuestions) const;

    // Reset
    void reset();
};

#endif
