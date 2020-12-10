#include "GameStateMachine.h"
#include "GameState.h"
#include "GameStateMainMenu.h"
#include "GameStateGameplay.h"

void GameStateMachine::ChangeState(const GameStateName stateName)
{
    GameState* pNewGameState{};
    switch (stateName)
    {
        case GameStateMachine::GameStateName::MAIN_MENU:
            pNewGameState = new GameStateMainMenu{ this };
            break;
        case GameStateMachine::GameStateName::GAMEPLAY:
            pNewGameState = new GameStateGameplay{ this };
            break;
    }
    StateMachine::ChangeState(pNewGameState);
    delete m_pCurrentGameState;
    m_pCurrentGameState = pNewGameState;
}
