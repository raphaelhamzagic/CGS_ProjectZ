#pragma once
#include "GameState.h"

class GameplayStateMachine;
class GameStateMachine;
class Level;

class GameStateGameplay : public GameState
{
    GameplayStateMachine* m_pGameplayStateMachine;
    Level* m_pLevel;

public:
    GameStateGameplay(GameStateMachine* pGameStateMachine);

    virtual void Draw() override;
    virtual bool Update(bool processInput) override;
};

