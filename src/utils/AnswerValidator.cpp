#include "utils/AnswerValidator.h"
#include "ui/ColorTheme.h"
#include <algorithm>
#include <iostream>

bool AnswerValidator::is_valid(const Question& question, const std::string& input) {
    return question.is_valid_input(input);
}

std::string AnswerValidator::get_error_message(const Question& question) {
    return "❌ Invalid input! " + question.get_input_prompt();
}

bool AnswerValidator::is_special_command(const std::string& input) {
    return parse_special_command(input) != SpecialCommand::None;
}

AnswerValidator::SpecialCommand AnswerValidator::parse_special_command(const std::string& input) {
    std::string lower = input;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "hint" || lower == "h") {
        return SpecialCommand::Hint;
    } else if (lower == "skip" || lower == "s") {
        return SpecialCommand::Skip;
    } else if (lower == "5050" || lower == "50/50") {
        return SpecialCommand::FiftyFifty;
    }

    return SpecialCommand::None;
}
