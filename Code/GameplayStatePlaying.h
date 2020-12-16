#pragma once
#include "GameplayState.h"

class GameStateGameplay;

class GameplayStatePlaying : public GameplayState
{
public:
    GameplayStatePlaying(GameStateGameplay* pGameStateGameplay);
    virtual bool Update(bool processInput) override;
    virtual void Draw();
};

