#pragma once
#include "State.h"

class GameStateGameplay;

class GameplayState : public State
{
protected:
    GameStateGameplay* m_pGameStateGameplay;

public:
    GameplayState(GameStateGameplay* pGameStateGameplay);    
};

