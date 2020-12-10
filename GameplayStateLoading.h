#pragma once
#include "GameplayState.h"
#include "GameStateGameplay.h"

class GameplayStateLoading : public GameplayState
{
public:
    GameplayStateLoading(GameStateGameplay* pGameStateGameplay);
    virtual void Draw() override;
    virtual bool Update(bool processInput) override;
};

