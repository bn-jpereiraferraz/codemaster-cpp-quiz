#ifndef IQUESTIONPROVIDER_H
#define IQUESTIONPROVIDER_H

#include "core/QuestionBank.h"

//==================
// QUESTION PROVIDER INTERFACE
//==================
// Focused interface for accessing questions
// Single Responsibility: Question data access
class IQuestionProvider {
public:
    virtual ~IQuestionProvider() = default;

    virtual QuestionBank& get_question_bank() = 0;
    virtual const QuestionBank& get_question_bank() const = 0;
};

#endif
