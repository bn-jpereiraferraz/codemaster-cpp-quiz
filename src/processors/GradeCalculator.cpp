#include "processors/GradeCalculator.h"
#include "ui/ColorTheme.h"

std::string GradeCalculator::calculate_grade(double percentage){
    if (percentage >= 97) return "A+";
    if (percentage >= 93) return "A";
    if (percentage >= 90) return "A-";
    if (percentage >= 87) return "B+";
    if (percentage >= 83) return "B";
    if (percentage >= 80) return "B-";
    if (percentage >= 77) return "C+";
    if (percentage >= 73) return "C";
    if (percentage >= 70) return "C-";
    if (percentage >= 67) return "D+";
    if (percentage >= 63) return "D";
    if (percentage >= 60) return "D-";
    return "F";
}

std::string GradeCalculator::get_grade_color(const std::string& grade){
    if (grade[0] == 'A') return ColorTheme::GREEN;
    if (grade[0] == 'B') return ColorTheme::CYAN;
    if (grade[0] == 'C') return ColorTheme::YELLOW;
    if (grade[0] == 'D') return ColorTheme::MAGENTA;
    return ColorTheme::RED;
}

bool GradeCalculator::is_passing(double percentage){
    return percentage >= 60.0;
}

