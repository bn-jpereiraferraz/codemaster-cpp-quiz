#include "utils/InputValidator.h"
#include "ui/ColorTheme.h"
#include <iostream>
#include <cctype>
#include <istream>


int InputValidator::get_int_in_range(const std::string& prompt, int min, int max){
    int value;

    while(true){
        std::cout << ColorTheme::YELLOW << prompt << ColorTheme::RESET;
        std::cin >> value;

        //check if wrong input
        if (std::cin.fail()){
            std::cin.clear();
            clear_input_buffer();
            show_error("Please enter a valid number!");
            continue;
        }

        clear_input_buffer();

        //check range
        if (value < min || value > max){
            show_error("Please enter a number between " + std::to_string(min) + " and " + std::to_string(max) + "!");
            continue;
        }
        return value;
    }
}

int InputValidator::get_int(const std::string& prompt){
    return get_int_in_range(prompt, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int InputValidator::get_menu_choice(const std::string& prompt, int numOptions){
    return get_int_in_range(prompt, 1, numOptions);
}

bool InputValidator::get_yes_no(const std::string& prompt){
    std::string input;

    while(true){
        std::cout << ColorTheme::YELLOW << prompt <<" (y/n): " << ColorTheme::RESET;
        std::getline(std::cin, input);

        if (input.empty()){
            show_error("Please enter y or n!");
            continue;
        }

        //convert to lowercase
        char c = std::tolower(input[0]);

        if (c == 'y') return true;
        if (c == 'n') return false;

        show_error("Please enter y or n!");
    }
}

std::string InputValidator::get_non_empty_string(const std::string& prompt){
    std::string input;

    while(true){
        std::cout << ColorTheme::YELLOW << prompt << ColorTheme::RESET;
        std::getline(std::cin, input);

        if (!is_whitespace_only(input)){
            return input;
        }
        show_error("Input cannot be empty!");
    }
}

std::string InputValidator::get_string(const std::string& prompt){
    std::string input;
    std::cout << ColorTheme::YELLOW << prompt << ColorTheme::RESET;
    std::getline(std::cin, input);
    return input;
}

void InputValidator::clear_input_buffer(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void InputValidator::show_error(const std::string& message){
    std::cout << ColorTheme::RED << "❌ " << message << ColorTheme::RESET << "\n";
}

bool InputValidator::is_whitespace_only(const std::string& str){
    if (str.empty()) return true;

    for (char c : str){
        if (!std::isspace(c)){
            return false;
        }
    }
    return true;
}