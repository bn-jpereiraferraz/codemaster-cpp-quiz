#ifndef COLORTHEME_H
#define COLORTHEME_H

//==================
// COLOR THEME - ANSI terminal styling
//==================
class ColorTheme {
public:
    // ANSI color codes (static = shared across instances)
    static const char* RESET;
    static const char* RED;
    static const char* GREEN;
    static const char* YELLOW;
    static const char* BLUE;
    static const char* MAGENTA;
    static const char* CYAN;
    static const char* BOLD;
    static const char* DIM;

    // Visual output methods
    static void print_banner();
    static void print_separator();
    static void print_correct_message(int points);
    static void print_wrong_message();
    static void print_question_header(int current, int total);
    static void print_progress_bar(int current, int total);
};

#endif
