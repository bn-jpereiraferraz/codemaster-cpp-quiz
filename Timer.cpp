#include "Timer.h"

//===================================
// TIMER CLASS IMPLEMENTATION
//===================================

Timer::Timer(int seconds)
    : timeLimit(seconds), running(false) {
    // Initializer list sets timeLimit and running to false
    // startTime will be set when start() is called
}

// Start the countdown timer
void Timer::start() {
    startTime = std::chrono::steady_clock::now();  // Record current time
    running = true;  // Mark as active
}

// Stop the timer
void Timer::stop() {
    running = false;  // Mark as inactive
}

// Get how many seconds have elapsed since the start
int Timer::get_elapsed_seconds() const {
    // Get current time
    auto now = std::chrono::steady_clock::now();

    // Calculate difference between now and start
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);

    // Return as integer seconds
    return elapsed.count();
}

// Get how many seconds remain
int Timer::get_remaining_seconds() const {
    int elapsed = get_elapsed_seconds();
    int remaining = timeLimit - elapsed;

    // Never return negative
    return (remaining > 0) ? remaining : 0;
}

// Check if time has expired
bool Timer::is_time_up() const {
    return get_remaining_seconds() == 0;
}

// Check if timer is currently running
bool Timer::is_running() const {
    return running;
}
