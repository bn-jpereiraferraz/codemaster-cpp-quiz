#include "core/GameSession.h"
#include "processors/GradeCalculator.h"

GameSession::GameSession()
    : earnedScore(0),
      totalScore(0),
      correctCount(0),
      wrongCount(0),
      currentStreak(0),
      bestStreak(0),
      totalBonusPoints(0),
      currentQuestionIndex(0),
      currentHintLevel(0) {
}

void GameSession::record_correct_answer(int points, int bonusPoints) {
    earnedScore += points + bonusPoints;
    correctCount++;
    currentStreak++;
    totalBonusPoints += bonusPoints;
    update_best_streak();
}

void GameSession::record_wrong_answer() {
    wrongCount++;
    reset_streak();
}

void GameSession::reset_streak() {
    currentStreak = 0;
}

void GameSession::update_best_streak() {
    if (currentStreak > bestStreak) {
        bestStreak = currentStreak;
    }
}

void GameSession::increment_hint_level() {
    currentHintLevel++;
}

void GameSession::reset_hint_level() {
    currentHintLevel = 0;
}

int GameSession::get_hint_level() const {
    return currentHintLevel;
}

void GameSession::set_current_question_index(int index) {
    currentQuestionIndex = index;
}

int GameSession::get_current_question_index() const {
    return currentQuestionIndex;
}

void GameSession::advance_question() {
    currentQuestionIndex++;
}

void GameSession::set_total_score(int score) {
    totalScore = score;
}

void GameSession::set_earned_score(int score) {
    earnedScore = score;
}

void GameSession::set_correct_count(int count) {
    correctCount = count;
}

void GameSession::set_current_streak(int streak) {
    currentStreak = streak;
}

void GameSession::set_best_streak(int streak) {
    bestStreak = streak;
}

void GameSession::set_total_bonus_points(int points) {
    totalBonusPoints = points;
}

int GameSession::get_earned_score() const {
    return earnedScore;
}

int GameSession::get_total_score() const {
    return totalScore;
}

int GameSession::get_correct_count() const {
    return correctCount;
}

int GameSession::get_wrong_count() const {
    return wrongCount;
}

int GameSession::get_current_streak() const {
    return currentStreak;
}

int GameSession::get_best_streak() const {
    return bestStreak;
}

int GameSession::get_total_bonus_points() const {
    return totalBonusPoints;
}

ResultsSummary GameSession::get_summary(size_t totalQuestions) const {
    ResultsSummary summary;
    summary.totalQuestions = totalQuestions;
    summary.correctAnswers = correctCount;
    summary.wrongAnswers = totalQuestions - correctCount;
    summary.score = earnedScore;
    summary.maxScore = totalScore;
    summary.bestStreak = bestStreak;
    summary.perfectScore = (earnedScore == totalScore);
    return summary;
}

void GameSession::reset() {
    earnedScore = 0;
    totalScore = 0;
    correctCount = 0;
    wrongCount = 0;
    currentStreak = 0;
    bestStreak = 0;
    totalBonusPoints = 0;
    currentQuestionIndex = 0;
    currentHintLevel = 0;
}
