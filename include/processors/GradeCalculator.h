#ifndef GRADECALCULATOR_H
#define GRADECALCULATOR_H
#include <string>

class GradeCalculator{
public:
    //Calculate letter grade from percentage
    static std::string calculate_grade(double percentage);

    //Get grad color for display
    static std::string get_grade_color(const std::string& grade);

    //Check if grade is passig (>= 60%)
    static bool is_passing(double percentage);
};
#endif // GRADECALCULATOR_H
