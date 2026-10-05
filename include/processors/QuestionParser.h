#ifndef QUESTIONPARSER_H
#define QUESTIONPARSER_H

#include "models/Question.h"
#include <string>
#include <vector>
#include <memory>

class QuestionParser {
public:
    // Parse a question from line (returns unique_ptr for memory safety)
    static std::unique_ptr<Question> parse_question_line(const std::string& line);

    // Parse multiple choice options
    static std::vector<std::string> parse_options(const std::string& optionsStr);

    // Validate question format
    static bool is_valid_format(const std::string& line);

    // Count fields in line
    static int count_fields(const std::string& line);

private:
    // Split line into fields by delimiter
    static std::vector<std::string> split_fields(const std::string& line);

    // Parse multiple choice question from fields
    static std::unique_ptr<Question> parse_multiple_choice(const std::vector<std::string>& fields);

    // Parse true or false question from field
    static std::unique_ptr<Question> parse_true_false(const std::vector<std::string>& fields);
};

#endif
