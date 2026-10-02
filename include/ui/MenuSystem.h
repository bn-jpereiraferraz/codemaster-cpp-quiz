#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H
#include <string>
#include <vector>

struct MenuItem{
    std::string label;
    std::string color;

    MenuItem(const std::string& l, const std::string& c = "")
        : label(l), color(c){}
};

class MenuSystem{
public:
    //Display Menu with title and options
    static void show_menu(const std::string& title, const std::vector<MenuItem>& items);

    //Display simple menu with numbered options
    static void show_simple_menu(const std::string& title, const std::vector<std::string>& options);

    //Display border title
    static void show_title(const std::string& title);
private:
    //Calculate Box width for centering
    static int calculate_box_width(const std::string& text);
};

#endif // MENUSYSTEM_H
