#include "utils/QuestionFile.h"
#include "processors/QuestionParser.h"
#include "core/GameExceptions.h"
#include "ui/ColorTheme.h"
#include <fstream>
#include <iostream>

std::vector<std::unique_ptr<Question>> QuestionFile::load_questions(const std::string& filename){
    std::vector<std::unique_ptr<Question>> questions;

    try {
        std::ifstream file(filename);

        if (!file.is_open()){
            // Return empty vector - caller will handle fallback
            return questions;
        }

        std::string line;
        int lineNumber = 0;

        while(std::getline(file, line)){
            lineNumber++;

            if (line.empty() || line[0] == '#'){
                continue;
            }

            try {
                std::unique_ptr<Question> question = QuestionParser::parse_question_line(line);
                if (question != nullptr){
                    questions.push_back(std::move(question));
                } else {
                    std::cout << ColorTheme::YELLOW << "Warning: Skipped invalid question at line "
                              << lineNumber << ColorTheme::RESET << std::endl;
                }
            } catch (const ParseException& e) {
                std::cerr << ColorTheme::YELLOW << "Warning at line " << lineNumber
                          << ": " << e.what() << ColorTheme::RESET << std::endl;
                // Continue parsing other questions
            }
        }

        file.close();

    } catch (const std::exception& e) {
        std::cerr << ColorTheme::RED << "Error loading questions from '"
                  << filename << "': " << e.what() << ColorTheme::RESET << std::endl;
        // Return whatever was successfully parsed
    }

    return questions;
}

bool QuestionFile::save_questions(const std::string& filename, const std::vector<Question*>& questions){
    (void)questions;  // Not implemented yet
    std::cout << ColorTheme::YELLOW << "Warning: Question saving not yet implemented for file: "
              << filename << ColorTheme::RESET << std::endl;
    return false;
}

int QuestionFile::count_questions(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) return 0;

    int count = 0;
    std::string line;

    while(std::getline(file, line)){
        if (!line.empty() && line[0] != '#'){
            count++;
        }
    }

    file.close();
    return count;
}

bool QuestionFile::file_exists(const std::string& filename){
    std::ifstream file(filename);
    return file.good();
}
