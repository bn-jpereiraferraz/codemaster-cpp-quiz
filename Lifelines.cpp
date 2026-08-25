#include "Lifelines.h"
#include "ColorTheme.h"
#include <iostream>

//==============================
// LIFELINES CLASS IMPLEMENTATION
//==============================

// Constructor - all lifelines start available
Lifelines::Lifelines()
    : fiftyFiftyAvailable(true), skipAvailable(true), hintAvailable(true) {
    // All lifelines ready to use
}

// Check if the 50/50 is available
bool Lifelines::can_use_fifty_fifty() const {
    return fiftyFiftyAvailable;
}

// Check if skip is available
bool Lifelines::can_use_skip() const {
    return skipAvailable;
}

// Check if hint is available
bool Lifelines::can_use_hint() const {
    return hintAvailable;
}

// Use 50/50 lifeline
bool Lifelines::use_fifty_fifty() {
    if (!fiftyFiftyAvailable) return false;  // Already used
    fiftyFiftyAvailable = false;  // Mark as used
    return true;  // Success
}

// Use skip lifeline
bool Lifelines::use_skip() {
    if (!skipAvailable) return false;  // Already used
    skipAvailable = false;  // Mark as used
    return true;  // Success
}

// Use hint lifeline
bool Lifelines::use_hint() {
    if (!hintAvailable) return false;  // Already used
    hintAvailable = false;  // Mark as used
    return true;  // Success
}

// Display available lifelines
void Lifelines::display_available() const {
    std::cout << ColorTheme::CYAN << "💡 Lifelines: " << ColorTheme::RESET;

    if (fiftyFiftyAvailable) {
        std::cout << ColorTheme::GREEN << "[50/50]" << ColorTheme::DIM << " (type '5050') " << ColorTheme::RESET;
    } else {
        std::cout << ColorTheme::DIM << "[Used] ";
    }

    if (skipAvailable) {
        std::cout << ColorTheme::GREEN << "[SKIP]" << ColorTheme::DIM << " (type 'skip') " << ColorTheme::RESET;
    } else {
        std::cout << ColorTheme::DIM << "[Used] ";
    }

    if (hintAvailable) {
        std::cout << ColorTheme::GREEN << "[HINT]" << ColorTheme::DIM << " (coming soon) " << ColorTheme::RESET;
    } else {
        std::cout << ColorTheme::DIM << "[Used]";
    }

    std::cout << std::endl;
}

// Reset all lifelines to available
void Lifelines::reset() {
    fiftyFiftyAvailable = true;
    skipAvailable = true;
    hintAvailable = true;
}

// Get state - is 50/50 used?
bool Lifelines::is_fifty_fifty_used() const {
    return !fiftyFiftyAvailable;
}

// Get state - is skip used?
bool Lifelines::is_skip_used() const {
    return !skipAvailable;
}

// Get state - is hint used?
bool Lifelines::is_hint_used() const {
    return !hintAvailable;
}

// Set 50/50 state (for loading saves)
void Lifelines::set_fifty_fifty_used(bool used) {
    fiftyFiftyAvailable = !used;
}

// Set skip state (for loading saves)
void Lifelines::set_skip_used(bool used) {
    skipAvailable = !used;
}

// Set hint state (for loading saves)
void Lifelines::set_hint_used(bool used) {
    hintAvailable = !used;
}
