#ifndef STATISTICSREPOSITORY_H
#define STATISTICSREPOSITORY_H

#include "systems/StatisticsData.h"
#include <string>

//==================
// STATISTICS REPOSITORY
//==================
// Handles file I/O persistence
class StatisticsRepository {
public:
    static bool save_to_file(const StatisticsData& data, const std::string& filename);
    static bool load_from_file(StatisticsData& data, const std::string& filename);
};

#endif
