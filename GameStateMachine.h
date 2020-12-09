#pragma once
#include "StateMachine.h"

class GameStateMachine : public StateMachine
{
public:

    enum class GameStateName
    {
        MAIN_MENU,
        OPTIONS,
        GAMEPLAY
    };

    // virtual bool UpdateState(bool processInput = true);
    // virtual void DrawCurrentState();
    // virtual void ChangeState(State* pNewState) override;
    void ChangeState(const GameStateName stateName);
};

