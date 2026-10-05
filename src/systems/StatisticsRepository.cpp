#include "systems/StatisticsRepository.h"
#include <fstream>

bool StatisticsRepository::save_to_file(const StatisticsData& data, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        return false;
    }

    // Save career stats
    outFile << data.totalGamesPlayed << "\n";
    outFile << data.totalQuestionsAnswered << "\n";
    outFile << data.totalCorrectAnswers << "\n";
    outFile << data.totalPointsEarned << "\n";
    outFile << data.longestStreakEver << "\n";

    // Save per mode arrays
    for (int i = 0; i < 6; i++) {
        outFile << data.gamesPlayedPerMode[i] << " ";
    }
    outFile << "\n";

    for (int i = 0; i < 6; i++) {
        outFile << data.correctPerMode[i] << " ";
    }
    outFile << "\n";

    for (int i = 0; i < 6; i++) {
        outFile << data.totalPerMode[i] << " ";
    }
    outFile << "\n";

    for (int i = 0; i < 6; i++) {
        outFile << data.highScorePerMode[i] << " ";
    }
    outFile << "\n";

    // Save category performance
    outFile << data.categoryTotal.size() << "\n";
    for (const auto& pair : data.categoryTotal) {
        outFile << pair.first << "|";
        outFile << pair.second << "|";

        auto it = data.categoryCorrect.find(pair.first);
        int correct = (it != data.categoryCorrect.end()) ? it->second : 0;
        outFile << correct << "\n";
    }

    // Save high scores for each mode
    for (int i = 0; i < 6; i++) {
        outFile << data.highScores[i].size() << "\n";
        for (const ScoreEntry& entry : data.highScores[i]) {
            outFile << entry.score << "|";
            outFile << entry.correctCount << "|";
            outFile << entry.totalQuestions << "|";
            outFile << entry.date << "\n";
        }
    }

    outFile.close();
    return true;
}

bool StatisticsRepository::load_from_file(StatisticsData& data, const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        return false;
    }

    // Load career stats
    inFile >> data.totalGamesPlayed;
    inFile >> data.totalQuestionsAnswered;
    inFile >> data.totalCorrectAnswers;
    inFile >> data.totalPointsEarned;
    inFile >> data.longestStreakEver;

    // Load per-mode arrays
    for (int i = 0; i < 6; i++) {
        inFile >> data.gamesPlayedPerMode[i];
    }

    for (int i = 0; i < 6; i++) {
        inFile >> data.correctPerMode[i];
    }

    for (int i = 0; i < 6; i++) {
        inFile >> data.totalPerMode[i];
    }

    for (int i = 0; i < 6; i++) {
        inFile >> data.highScorePerMode[i];
    }

    // Load category performance
    int categoryCount;
    inFile >> categoryCount;
    inFile.ignore();

    for (int i = 0; i < categoryCount; i++) {
        std::string line;
        std::getline(inFile, line);

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        std::string category = line.substr(0, pos1);
        int total = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        int correct = std::stoi(line.substr(pos2 + 1));

        data.categoryTotal[category] = total;
        data.categoryCorrect[category] = correct;
    }

    // Load high scores for each mode
    for (int i = 0; i < 6; i++) {
        int scoreCount;
        inFile >> scoreCount;
        inFile.ignore();

        data.highScores[i].clear();

        for (int j = 0; j < scoreCount; j++) {
            std::string line;
            std::getline(inFile, line);

            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            ScoreEntry entry;
            entry.score = std::stoi(line.substr(0, pos1));
            entry.correctCount = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            entry.totalQuestions = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            entry.date = line.substr(pos3 + 1);

            data.highScores[i].push_back(entry);
        }
    }

    inFile.close();
    return true;
}
