#ifndef QUESTIONFILE_H
#define QUESTIONFILE_H

#include "models/Question.h"
#include <vector>
#include <string>
#include <memory>

class QuestionFile {
public:
    // Load Questions from file (returns unique_ptrs for memory safety)
    static std::vector<std::unique_ptr<Question>> load_questions(const std::string& filename);

    // Save questions to file
    static bool save_questions(const std::string& filename, const std::vector<Question*>& questions);

    // Count questions in file
    static int count_questions(const std::string& filename);

    // Check if file exists
    static bool file_exists(const std::string& filename);
};

#endif
