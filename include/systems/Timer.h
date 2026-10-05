#ifndef TIMER_H
#define TIMER_H

#include <chrono>

//==================
// TIMER - Per-Question Countdown Timer
//==================
// Purpose: Track time limit for INDIVIDUAL questions
//
// Use Cases:
// - Timed mode: Each question has 30/60 seconds
// - Time bonus calculation (faster answer = more points)
// - Display countdown progress bar
//
// NOT for:
// - Global game timers (use GlobalTimer instead)
// - Session-wide countdown with penalties
//
// Example:
//   Timer questionTimer(30);  // 30 seconds for this question
//   questionTimer.start();
//   // ... player answers ...
//   int timeUsed = questionTimer.get_elapsed_seconds();
//==================
class Timer {
private:
    int timeLimit;  // Seconds allowed
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    bool running;

public:
    Timer(int seconds);  // Initialize with time limit

    void start();  // Begin countdown
    void stop();   // End countdown

    int get_elapsed_seconds() const;   // Time used so far
    int get_remaining_seconds() const; // Time left
    bool is_time_up() const;           // Check if expired
    void display_progress_bar()const; //Countdown bar
    bool is_running() const;           // Check if active
};

#endif
