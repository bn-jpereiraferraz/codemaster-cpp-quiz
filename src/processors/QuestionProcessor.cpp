#include "processors/QuestionProcessor.h"
#include "core/Constants.h"
#include <algorithm>
#include <random>
#include <chrono>

void QuestionProcessor::shuffle_questions(std::vector<Question*>& questions){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(questions.begin(), questions.end(), std::default_random_engine(seed));
}

std::vector<Question*> QuestionProcessor::filter_by_difficulty(const std::vector<Question*>& questions, const std::string& difficulty){
    if (difficulty == GameConstants::DIFF_MIXED) return questions;

    std::vector<Question*> filtered;
    for (Question* question : questions){
        if (question->get_difficulty() == difficulty){
            filtered.push_back(question);
        }
    }
    return filtered;
}

std::vector<Question*> QuestionProcessor::filter_by_category(const std::vector<Question*>& questions, const std::string& category){
    if (category == GameConstants::CATEGORY_ALL) return questions;

    std::vector<Question*> filtered;

    for(Question* question : questions){
        if (question->get_category() == category){
            filtered.push_back(question);
        }
    }
    return filtered;
}

std::vector<Question*> QuestionProcessor::select_random(const std::vector<Question*>& questions, int count){
    if (count >= (int)questions.size()) return questions;

    std::vector<Question*> shuffled = questions;
    shuffle_questions(shuffled);

    std::vector<Question*> selected;
    for (int i = 0; i < count && i < (int)shuffled.size(); i++){
        selected.push_back(shuffled[i]);
    }
    return selected;
}

void QuestionProcessor::sort_by_difficulty(std::vector<Question*>& questions){
    std::sort(questions.begin(), questions.end(), [](Question* a, Question* b){
        std::string diffA = a->get_difficulty();
        std::string diffB = b->get_difficulty();

        auto getDiffValue = [](const std::string& diff) -> int {
            if (diff == "Easy") return 1;
            if (diff == "Medium") return 2;
            if (diff == "Hard") return 3;

            return 0;
        };
        return getDiffValue(diffA) < getDiffValue(diffB);
    });
}