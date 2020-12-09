#include "GameStateMachine.h"
#include "GameStateMainMenu.h"
#include "State.h"
#include "StateMachine.h"

void GameStateMachine::ChangeState(const GameStateName stateName)
{
    State* pNewState{};
    switch (stateName)
    {
        case GameStateMachine::GameStateName::MAIN_MENU:
            pNewState = new GameStateMainMenu{ this };
            break;
    }
    StateMachine::ChangeState(pNewState);
}
