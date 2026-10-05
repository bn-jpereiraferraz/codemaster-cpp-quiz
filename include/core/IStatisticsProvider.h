#ifndef ISTATISTICSPROVIDER_H
#define ISTATISTICSPROVIDER_H

#include "systems/statistics.h"

//==================
// STATISTICS PROVIDER INTERFACE
//==================
// Focused interface for statistics access
// Single Responsibility: Statistics management
class IStatisticsProvider {
public:
    virtual ~IStatisticsProvider() = default;

    virtual Statistics& get_statistics() = 0;
    virtual const Statistics& get_statistics() const = 0;
};

#endif
