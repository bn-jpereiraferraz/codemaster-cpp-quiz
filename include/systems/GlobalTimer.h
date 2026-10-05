#ifndef GLOBALTIMER_H
#define GLOBALTIMER_H
#include <chrono>

//==============================================
// GLOBAL TIMER - Session-Wide Countdown Timer
//==============================================
// Purpose: Track TOTAL time for entire game session with penalty system
//
// Key Differences from Timer:
// - Timer:       Per-question countdown (30s for THIS question)
// - GlobalTimer: Session-wide countdown (5min TOTAL for entire quiz)
//
// Key Features:
// - Session-level countdown (starts at X minutes, counts to 0)
// - Penalty system (wrong answer = deduct time)
// - Used in Quick Attack mode and similar time-pressure modes
//
// Usage Example:
//   GlobalTimer sessionTimer(300);  // 5 minutes TOTAL for quiz
//   sessionTimer.start();
//
//   // Player gets question wrong
//   sessionTimer.apply_penalty(15);  // -15 seconds from total time
//
//   if (sessionTimer.is_time_up()) {
//       // Game Over! Total time expired
//   }
//
// Why Both Timer and GlobalTimer Exist:
// - Some modes need per-question timers (Lightning: 10s each)
// - Some modes need session timers with penalties (Quick Attack: 5min total)
// - Some modes need BOTH (timed questions within a session limit)
//==============================================

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