#pragma once
#include "GameplayState.h"
#include "GameStateGameplay.h"

class GameplayStateLoading : public GameplayState
{
public:
    GameplayStateLoading(GameplayStateMachine* pGameplayStateMachine);
    virtual void Draw() override;
    virtual bool Update(bool processInput) override;
};

