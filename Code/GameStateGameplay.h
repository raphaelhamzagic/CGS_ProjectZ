#pragma once
#include "GameState.h"

class GameStateMachine;
class Level;

class GameStateGameplay : public GameState
{
    enum class GameplayState
    {
        LOADING,
        PLAYING,
        WIN_TRANSITION,
        LOSE_TRANSITION
    };
    GameplayState m_state;
    Level* m_pLevel;

public:   
    GameStateGameplay(GameStateMachine* pGameStateMachine);

    virtual void Draw() override;
    virtual bool Update(bool processInput) override;

    Level* LevelGet();

private:
    bool PlayingStateUpdate(bool processInput);
    void PlayingStateDraw();
};

