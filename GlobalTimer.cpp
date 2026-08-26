#include "GlobalTimer.h"

//===========
//CONSTRUCTOR
//===========
//Initialize with a countdown duration
//Parameters: 
//seconds - Starting time in seconds
GlobalTimer::GlobalTimer(int seconds)
    :totalSeconds(seconds), penaltySeconds(0), running(false){
        //Timer starts paused - call start() to begin countdown
    }

//============
//START
//============
//Begin countdown from current remaining time
void GlobalTimer::start(){
    if (!running){
        startTime = std::chrono::steady_clock::now(); //Mark start time
        running = true;
    }
}


//==========
//STOP
//==========
//Pause countdown(can be resumed with start())
void GlobalTimer::stop(){
    running = false;
}

//===========
//RESET
//===========
//Reset Timer to initial state(clear penalties, reset to full time)
void GlobalTimer::reset(){
    penaltySeconds = 0;
    running = false;
    //Next start() will begin fresh countdown
}

//==================
//APPLY PENALTY
//==================
//Subtract time from remaining seconds
//Parameters: seconds - Amount of time to deduct
//EXAMPLE: timer.apply_penalty(15); //Deduct 15 seconds for wrong answer
void GlobalTimer::apply_penalty(int seconds){
    penaltySeconds += seconds;
    //Note penalties accumulate and reduce remaining time
}

//==========================
//GET ELAPSED SECONDS
//==========================
//Calculate how many seconds have passed since start()
//returns Elapsed time in seconds
int GlobalTimer::get_elapsed_seconds()const{
    if (!running){
        return 0; //Timer paused, no time passing
    }
    //Calculate duration since start
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
    return static_cast<int>(duration.count());
}



//=======================
//GET REMAINING SECONDS
//=======================
//Calculate how much time is left on the countdown
//FORMULA: remaining = total - elapsed - penalties
//RETURNS: Remaining seconds (can be negative if overtime)
int GlobalTimer::get_remaining_seconds()const{
    int elapsed = get_elapsed_seconds();
    int remaining = totalSeconds - elapsed - penaltySeconds;
    return remaining; //Can be negative if time runs out
}

//================
//IS TIME UP
//================
//Check if countdown has reached zero or below
//RETURNS: true if no time remaining, false otherwise
bool GlobalTimer::is_time_up()const{
    return get_remaining_seconds() <= 0;
}

//=============
//IS RUNNING
//=============
//Check if timer is currently active
//RETURNS: true if counting down, false if paused
bool GlobalTimer::is_running()const{
    return running;
}