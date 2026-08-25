#ifndef LIFELINES_H
#define LIFELINES_H

//==================
// LIFELINES - Game show style helps
//==================
// Each can only be used ONCE per game
class Lifelines {
private:
    bool fiftyFiftyAvailable;  // Remove 2 wrong answers (MC only)
    bool skipAvailable;        // Skip question (no penalty)
    bool hintAvailable;        // Show hint (future feature)

public:
    Lifelines();

    // Check availability
    bool can_use_fifty_fifty() const;
    bool can_use_skip() const;
    bool can_use_hint() const;

    // Consume lifeline (returns false if already used)
    bool use_fifty_fifty();
    bool use_skip();
    bool use_hint();

    void display_available() const;  // Show available helps
    void reset();                    // Make all available again

    // Save/Load state
    bool is_fifty_fifty_used() const;
    bool is_skip_used() const;
    bool is_hint_used() const;

    void set_fifty_fifty_used(bool used);
    void set_skip_used(bool used);
    void set_hint_used(bool used);
};

#endif
