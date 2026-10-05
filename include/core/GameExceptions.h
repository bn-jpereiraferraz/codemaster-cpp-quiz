#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include <stdexcept>
#include <string>

//==================
// GAME EXCEPTION HIERARCHY
//==================
// Custom exceptions for better error handling

// Base exception for all game-related errors
class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message)
        : std::runtime_error(message) {}
};

// File I/O related errors
class FileException : public GameException {
public:
    explicit FileException(const std::string& filename, const std::string& reason)
        : GameException("File error '" + filename + "': " + reason),
          filename_(filename) {}

    const std::string& get_filename() const { return filename_; }

private:
    std::string filename_;
};

// Question parsing errors
class ParseException : public GameException {
public:
    explicit ParseException(const std::string& message, int line = -1)
        : GameException(line >= 0 ?
            "Parse error at line " + std::to_string(line) + ": " + message :
            "Parse error: " + message),
          line_number_(line) {}

    int get_line_number() const { return line_number_; }

private:
    int line_number_;
};

// Invalid game state errors
class InvalidStateException : public GameException {
public:
    explicit InvalidStateException(const std::string& message)
        : GameException("Invalid state: " + message) {}
};

// Configuration errors
class ConfigurationException : public GameException {
public:
    explicit ConfigurationException(const std::string& message)
        : GameException("Configuration error: " + message) {}
};

// Save/Load errors
class SaveLoadException : public GameException {
public:
    explicit SaveLoadException(const std::string& message)
        : GameException("Save/Load error: " + message) {}
};

#endif
