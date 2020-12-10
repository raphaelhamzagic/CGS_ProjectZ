#pragma once
#include "StateMachine.h"

class GameplayState;
class Level;

class GameplayStateMachine : public StateMachine
{
    GameplayState* m_pCurrentGameplayState;
    Level* m_pLevel;

public:
    enum class GameplayStateName
    {
        LOADING,
        PLAYING,
        WIN_TRANSITION,
        LOSE_TRANSITION
    };
    void ChangeState(const GameplayStateName stateName);
};

