#ifndef IGAMESTATE_H
#define IGAMESTATE_H

#include "core/IQuestionProvider.h"
#include "core/IScoreTracker.h"
#include "core/IGameplayState.h"
#include "core/IConfigurationProvider.h"
#include "core/IStatisticsProvider.h"

//==================
// GAME STATE INTERFACE (Composite)
//==================
// Composite interface combining all focused interfaces
// Uses Interface Segregation Principle - clients can depend on specific interfaces
class IGameState : public IQuestionProvider,
                   public IScoreTracker,
                   public IGameplayState,
                   public IConfigurationProvider,
                   public IStatisticsProvider {
public:
    ~IGameState() override = default;

    // All methods inherited from specific interfaces:
    // - IQuestionProvider: get_question_bank()
    // - IScoreTracker: get_session()
    // - IGameplayState: get_lifelines(), get_lives(), get_global_timer()
    // - IConfigurationProvider: get_configuration()
    // - IStatisticsProvider: get_statistics()
};

#endif
