#pragma once
#include "State.h"

class GameplayStateMachine;
class Level;

class GameplayState : public State
{
public:
    GameplayState(GameplayStateMachine* pGameplayStateMachine);
    virtual bool Update(bool processInput, Level* pLevel) = 0;

protected:
    GameplayStateMachine* m_pGameplayStateMachine;
};

