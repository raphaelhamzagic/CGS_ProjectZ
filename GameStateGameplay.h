#pragma once
#include "GameState.h"

class GameplayState;
class GameStateMachine;
class Level;

class GameStateGameplay : public GameState
{  
    GameplayState* m_pCurrentState;
    Level* m_pLevel;

public:
    enum class GameplayStateName
    {
        LOADING,
        PLAYING,
        WIN_TRANSITION,
        LOSE_TRANSITION
    };

    GameStateGameplay(GameStateMachine* pGameStateMachine);

    virtual void Draw() override;
    virtual bool Update(bool processInput) override;
    void StateChange(const GameplayStateName stateName);
    
    Level* GetLevel();

private:
    void CurrentStateExit();
};

