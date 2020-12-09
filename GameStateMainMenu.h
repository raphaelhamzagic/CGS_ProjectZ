#pragma once
#include "State.h"

class GameStateMachine;

class GameStateMainMenu : public State
{
    GameStateMachine* m_pGameStateMachine;
    bool m_isInvalidInput;
    enum class MenuOption
    {
        PLAY = 1,
        OPTIONS,
        EXIT,
    };

public:
    GameStateMainMenu(GameStateMachine* pGameStateMachine);

    virtual bool Update(bool processInput) override;
    virtual void Draw() override;

private:
    bool ProcessInput();
};

