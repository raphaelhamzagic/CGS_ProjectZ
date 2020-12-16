#include "GameplayState.h"
#include "GameStateGameplay.h"

GameplayState::GameplayState(GameStateGameplay* pGameStateGameplay)
    : m_pGameStateGameplay{ pGameStateGameplay }
{
}

bool GameplayState::Update(bool processInput)
{
    return false;
}
