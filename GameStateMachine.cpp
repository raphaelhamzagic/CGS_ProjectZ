#include "GameStateMachine.h"
#include "State.h"
#include "GameStateMainMenu.h"

void GameStateMachine::ChangeState(GameState state)
{
    State* pNewState{};
    switch (state)
    {
        case GameStateMachine::GameState::MAIN_MENU:
            pNewState = new GameStateMainMenu;
            break;
    }
    ChangeState(pNewState);
}
