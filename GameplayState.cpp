#include "GameplayState.h"
#include "GameplayStateMachine.h"

GameplayState::GameplayState(GameplayStateMachine* pGameplayStateMachine)
    : m_pGameplayStateMachine{ pGameplayStateMachine }
{
}
