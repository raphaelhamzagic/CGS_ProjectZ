#pragma once
#include "StateMachine.h"

class GameState;

class GameStateMachine : public StateMachine
{
    GameState* m_pCurrentGameState;

public:
    enum class GameStateName
    {
        GAMEPLAY,
        MAIN_MENU,
        OPTIONS
    };
    void ChangeState(const GameStateName stateName);    
};
