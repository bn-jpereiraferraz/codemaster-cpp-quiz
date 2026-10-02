#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <string>
#include <vector>

class StringUtils{
public:
    //Remove leading and trailing whitespace
    static std::string trim(const std::string& str);

    //Convert string to lower case
    static std::string toLower(const std::string& str);

    //Convert string to upper case
    static std::string toUpper(const std::string& str);

    //Split string by delimiter
    static std::vector<std::string> split(const std::string& str, char delimiter);

    //Check if string starts with prefix
    static bool starts_with(const std::string& str, const std::string& prefix);

    //Check if string ends with suffix
    static bool ends_with(const std::string& str, const std::string& suffix);

    //Replace all occurrences of 'from' with 'to'
    static std::string replace_all(const std::string& str, const std::string& from, const std::string& to);

private:
    //check if character is whitespace
    static bool is_whitespace(char c);
};

#endif // STRINGUTILS_H
