#include "Timer.h"
#include "ColorTheme.h"
#include <string>
#include <iostream>
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

//Display the Countdown bar
void Timer::display_progress_bar()const{
    int remaining = get_remaining_seconds();
    int elapsed = get_elapsed_seconds();

    //Don't display if no time limit configured
    if (timeLimit <= 0) return;

    //Calculate percentage remaining(0-100)
    double percentRemaining = ((double)remaining / timeLimit) * 100.0;

    //Choose color based on percentage
    std::string color;
    if (percentRemaining > 50.0){
        color = ColorTheme::GREEN;
    }else if (percentRemaining > 25.0){
        color = ColorTheme::YELLOW;
    }else{
        color = ColorTheme::RED;
    }

    //Bar width
    int totalBlocks = 20;
    int filledBlocks = (int)((percentRemaining / 100.0) * totalBlocks);
    int emptyBlocks = totalBlocks - filledBlocks;

    //Display Bar
    std::cout << color << "⏱️  [";

    //Filled 
    for (int i = 0; i < filledBlocks; i++){
        std::cout << "█";
    }

    //Empty
    for (int i = 0; i < emptyBlocks; i++){
        std::cout << "░";
    }

    //Show remaining seconds
    std::cout << "] " << remaining << "s remaining" << ColorTheme::RESET << std::endl;
}