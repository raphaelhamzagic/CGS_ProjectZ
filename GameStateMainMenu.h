#pragma once
#include "State.h"

class GameStateMachine;

class GameStateMainMenu : public State
{
    GameStateMachine* m_pGameStateMachine;
    bool m_isInvalidInput;
    enum class MenuOption
    {
        OPTIONS = 1,
        PLAY,
        EXIT,
    };

public:
    GameStateMainMenu(GameStateMachine* pGameStateMachine);

    virtual bool Update(bool processInput) override;
    virtual void Draw() override;

private:
    bool ProcessInput();
};

