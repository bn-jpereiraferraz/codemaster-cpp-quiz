#ifndef QUESTIONPROCESSOR_H
#define QUESTIONPROCESSOR_H
#include "models/Question.h"
#include <vector>
#include <string>

class QuestionProcessor {
public:
    //Shuffle questions randomly
    static void shuffle_questions(std::vector<Question*>& questions);

    //Filter by difficulty
    static std::vector<Question*> filter_by_difficulty(const std::vector<Question*>& questions, const std::string& difficulty);

    //Filter by Category
    static std::vector<Question*> filter_by_category(const std::vector<Question*>& questions, const std::string& category);

    //Select N random questions
    static std::vector<Question*> select_random(const std::vector<Question*>& questions, int count);

    //Sort questions by difficulty
    static void sort_by_difficulty(std::vector<Question*>& questions);
};

#endif // QUESTIONPROCESSOR_H
