#pragma once
#include "GameplayState.h"

class GameStateGameplay;

class GameplayStateLoading : public GameplayState
{
public:
    GameplayStateLoading(GameStateGameplay* pGameStateGameplay);
    virtual void Draw() override;
};

