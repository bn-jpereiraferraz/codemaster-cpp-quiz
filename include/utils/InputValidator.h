#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H
#include <string>
#include <limits>

class InputValidator{
public:
    //Get Valid integer in range
    static int get_int_in_range(const std::string& prompt, int min, int max);
    
    //Get valid integer (any value)
    static int get_int(const std::string& prompt);
    
    //Get validated menu choice (1 to numerous options)
    static int get_menu_choice(const std::string& prompt, int numOptions);
    
    //Return true for yes and false for no
    static bool get_yes_no(const std::string& prompt);
    
    //loops until non-whitespace input
    static std::string get_non_empty_string(const std::string& prompt);

    //get any string even empty
    static std::string get_string(const std::string& prompt);

private:
    //clear input buffer after failed cin operation
    static void clear_input_buffer();

    //Display error message
    static void show_error(const std::string& message);

    //check if string empty or whitespace
    static bool is_whitespace_only(const std::string& str);
};

#endif //INPUTVALIDATOR_H
