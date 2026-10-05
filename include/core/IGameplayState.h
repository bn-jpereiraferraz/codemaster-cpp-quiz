#ifndef IGAMEPLAYSTATE_H
#define IGAMEPLAYSTATE_H

#include "systems/Lifelines.h"
#include "systems/Lives.h"
#include "systems/GlobalTimer.h"

//==================
// GAMEPLAY STATE INTERFACE
//==================
// Focused interface for game systems (lifelines, lives, timer)
// Single Responsibility: Gameplay mechanics access
class IGameplayState {
public:
    virtual ~IGameplayState() = default;

    virtual Lifelines& get_lifelines() = 0;
    virtual const Lifelines& get_lifelines() const = 0;

    virtual Lives& get_lives() = 0;
    virtual const Lives& get_lives() const = 0;

    virtual GlobalTimer& get_global_timer() = 0;
    virtual const GlobalTimer& get_global_timer() const = 0;
};

#endif
