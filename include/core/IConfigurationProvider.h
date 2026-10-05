#ifndef ICONFIGURATIONPROVIDER_H
#define ICONFIGURATIONPROVIDER_H

#include "core/GameConfiguration.h"

//==================
// CONFIGURATION PROVIDER INTERFACE
//==================
// Focused interface for game configuration access
// Single Responsibility: Configuration management
class IConfigurationProvider {
public:
    virtual ~IConfigurationProvider() = default;

    virtual GameConfiguration& get_configuration() = 0;
    virtual const GameConfiguration& get_configuration() const = 0;
};

#endif
