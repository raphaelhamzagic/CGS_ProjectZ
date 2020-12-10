#pragma once
#include "State.h"

class GameStateMachine;

class GameState : public State
{
public:
    GameState(GameStateMachine* pGameStateMachine);

protected:
    GameStateMachine* m_pGameStateMachine;
};

