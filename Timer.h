#ifndef TIMER_H
#define TIMER_H

#include <chrono>

//==================
// TIMER - Countdown for each question
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
    bool is_running() const;           // Check if active
};

#endif
