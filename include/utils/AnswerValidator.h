#ifndef ANSWERVALIDATOR_H
#define ANSWERVALIDATOR_H

#include "models/Question.h"
#include <string>

//==================
// ANSWER VALIDATOR
//==================
// Validates user input for questions
// Single Responsibility: Input Validation
class AnswerValidator {
public:
    // Validate answer format for a question
    static bool is_valid(const Question& question, const std::string& input);

    // Get error message for invalid input
    static std::string get_error_message(const Question& question);

    // Check if input is a special command (hint, skip, 5050)
    static bool is_special_command(const std::string& input);

    // Determine which special command
    enum class SpecialCommand {
        None,
        Hint,
        Skip,
        FiftyFifty
    };

    static SpecialCommand parse_special_command(const std::string& input);
};

#endif
