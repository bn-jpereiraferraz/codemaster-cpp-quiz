#include "utils/StringUtils.h"
#include <cctype>
#include <algorithm>

std::string StringUtils::trim(const std::string& str){
    if (str.empty()) return str;

    size_t start = 0;
    size_t end = str.length() - 1;

    //find first non whitespace
    while (start <= end && is_whitespace(str[start])){
        start++;
    }

    //find last non whitespace
    while (end >= start && is_whitespace(str[end])){
        end--;
    }

    return str.substr(start, end - start + 1);
}

std::string StringUtils::toLower(const std::string& str){
    std::string result = str;

    std::transform(result.begin(), result.end(), result.begin(),
    [](unsigned char c){return std::tolower(c);});

    return result;
}

std::string StringUtils::toUpper(const std::string& str){
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
    [](unsigned char c){return std::toupper(c);});

    return result;
}

std::vector<std::string> StringUtils::split(const std::string& str, char delimiter){
    std::vector<std::string> tokens;
    std::string token;
    size_t start = 0;
    size_t pos = str.find(delimiter);

    while(pos != std::string::npos){
        token = str.substr(start, pos - start);
        tokens.push_back(token);
        start = pos + 1;
        pos = str.find(delimiter, start);
    }

    //add last token
    tokens.push_back(str.substr(start));
    return tokens;
}

bool StringUtils::starts_with(const std::string& str, const std::string& prefix){
    if (prefix.length() > str.length()) return false;

    return str.substr(0, prefix.length()) == prefix;
}

bool StringUtils::ends_with(const std::string& str, const std::string& suffix){
    if (suffix.length() > str.length()) return false;

    return str.substr(str.length() - suffix.length()) == suffix;
}

std::string StringUtils::replace_all(const std::string& str, const std::string& from, const std::string& to){
    if (from.empty()) return str;

    std::string result = str;
    size_t pos = 0;

    while ((pos = result.find(from, pos)) != std::string::npos){
        result.replace(pos, from.length(), to);
        pos += to.length();
    }

    return result;
}

bool StringUtils::is_whitespace(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

