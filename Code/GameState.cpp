#include "GameState.h"
#include "GameStateMachine.h"

GameState::GameState(GameStateMachine* pGameStateMachine)
    : m_pGameStateMachine{pGameStateMachine}
{
}
