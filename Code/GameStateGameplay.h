#pragma once
#include "GameState.h"

class GameplayState;
class GameStateMachine;
class Level;

class GameStateGameplay : public GameState
{  
    GameplayState* m_pState;
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
    
    Level* LevelGet();

private:
    void StateExit();
};

