#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H
#include <string>

struct Achievement{
    std::string name;   //Achievement name
    std::string description;    //What it takes to earn it
    std::string icon;   //Emoji or symbol
    bool unlocked;  //Has user earned it
    std::string dateUnlocked;   //When it was earned(empty if not earned)

    Achievement(const std::string& n, const std::string& desc, const std::string& ic)
        :name(n), description(desc), icon(ic), unlocked(false), dateUnlocked(""){}
};

#endif // ACHIEVEMENT_H
