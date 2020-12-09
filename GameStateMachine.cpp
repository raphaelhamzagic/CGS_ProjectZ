#include "GameStateMachine.h"
#include "GameStateMainMenu.h"
#include "State.h"
#include "StateMachine.h"

void GameStateMachine::ChangeState(const GameStateName state)
{
    State* pNewState{};
    switch (state)
    {
        case GameStateMachine::GameStateName::MAIN_MENU:
            pNewState = new GameStateMainMenu{ this };
            break;
    }
    StateMachine::ChangeState(pNewState);
}
