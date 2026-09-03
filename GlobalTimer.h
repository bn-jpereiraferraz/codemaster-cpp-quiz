#ifndef GLOBALTIMER_H
#define GLOBALTIMER_H
#include <chrono>
//==============================================
//GLOBAL COUNTDOWN TIMER - For Quick Attack Mode
//==============================================
/*
Unlike Timer(which tracks the time we need per question),
GlobalTimer is a session wide countdown from a starting value

Key Features:
-Starts at a specified duration(300 seconds = 5 minutes)
-Counts down to zero
-Supports penalties
-Checks if time has run out

Usage: 
GlobalTimer timer(300); //5 min
timer.start();

//Wrong answer? Deduct 15 seconds
timer.apply_penalty(15);

if (timer.is_time:up())
    //Game Over!
==================================================
*/

class GlobalTimer{
    
    private: 
    
        //===Time Tracking===
        std::chrono::steady_clock::time_point startTime; //When timer started
        int totalSeconds; //Initial time limit
        int penaltySeconds; //Accumulated time penalties
        bool running; //is timer currently active
    
    public:
        
    //===CONSTRUCTION===
        GlobalTimer(int seconds); //Constructor: set initial time
        
        //===Timer Control===
        void start(); //Begin Countdown
        void stop(); //Pause countdown
        void reset(); //Reset to initial time
        
        //=== Time Penalties ===
        void apply_penalty(int seconds); //subtract time when wrong

        void display_progress_bar()const;

        //=== Time Queries ===
        int get_elapsed_seconds()const; //how many sec have passed
        int get_remaining_seconds()const; //How many sec are left
        bool is_time_up()const; //Has countdown reached 0
        bool is_running()const; //is timer active
};

#endif