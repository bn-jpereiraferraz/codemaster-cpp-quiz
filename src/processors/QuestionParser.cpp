#include "processors/QuestionParser.h"
#include "models/MultipleChoiceQuestion.h"
#include "models/TrueFalseQuestion.h"
#include "utils/StringUtils.h"

std::unique_ptr<Question> QuestionParser::parse_question_line(const std::string& line){
    if (!is_valid_format(line)) return nullptr;

    std::vector<std::string> fields = split_fields(line);
    if (fields.empty()) return nullptr;

    std::string type = fields[0];

    if (type == "MC"){
        return parse_multiple_choice(fields);
    }else if (type == "TF"){
        return parse_true_false(fields);
    }
    return nullptr;
}

std::vector<std::string> QuestionParser::parse_options(const std::string& optionsStr){
    return StringUtils::split(optionsStr, ',');
}

bool QuestionParser::is_valid_format(const std::string& line){
    return count_fields(line) >= 8;
}

int QuestionParser::count_fields(const std::string& line){
    int count = 1;
    for (char c : line){
        if (c == '|') count++;
    }
    return count;
}

std::vector<std::string> QuestionParser::split_fields(const std::string& line){
    std::vector<std::string> fields;
    size_t start = 0;
    size_t pos = line.find('|');

    while (pos != std::string::npos){
        fields.push_back(line.substr(start, pos - start));
        start  = pos + 1;
        pos  = line.find('|', start);
    }
    fields.push_back(line.substr(start));

    return fields;
}

std::unique_ptr<Question> QuestionParser::parse_multiple_choice(const std::vector<std::string>& fields){
    if (fields.size() < 9) return nullptr;

    std::string category = fields[1];
    std::string questionText = fields[2];
    int points = std::stoi(fields[3]);
    std::string optionsStr = fields[4];
    std::string answer = fields[5];
    std::string hint1 = fields[6];
    std::string hint2 = fields[7];
    std::string hint3 = fields[8];

    std::vector<std::string> options = parse_options(optionsStr);

    std::string difficulty = "Medium";

    return std::make_unique<MultipleChoiceQuestion>(category, difficulty, questionText,
                                                     options, answer, points,
                                                     hint1, hint2, hint3);
}

std::unique_ptr<Question> QuestionParser::parse_true_false(const std::vector<std::string>& fields){
    if (fields.size() < 8) return nullptr;

    std::string category = fields[1];
    std::string questionText = fields[2];
    int points = std::stoi(fields[3]);
    std::string answer = fields[4];
    std::string hint1 = fields[5];
    std::string hint2 = fields[6];
    std::string hint3 = fields[7];

    std::string difficulty = "Medium";

    return std::make_unique<TrueFalseQuestion>(category, difficulty, questionText,
                                                answer, points,
                                                hint1, hint2, hint3);
}

