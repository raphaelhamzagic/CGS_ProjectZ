#include "GameStateGameplay.h"
#include "GameplayStateMachine.h"
#include "Level.h"

GameStateGameplay::GameStateGameplay(GameStateMachine* pGameStateMachine)
    : GameState{ pGameStateMachine }
    , m_pLevel{ new Level }
    , m_pGameplayStateMachine{ new GameplayStateMachine }
{
}

void GameStateGameplay::Draw()
{
    m_pGameplayStateMachine->DrawCurrentState();
}

bool GameStateGameplay::Update(bool processInput)
{
    return m_pGameplayStateMachine->UpdateCurrentState(processInput);
}
