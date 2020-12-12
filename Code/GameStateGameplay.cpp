#include "GameStateGameplay.h"
#include "GameplayState.h"
#include "GameplayStateLoading.h"
#include "Level.h"

GameStateGameplay::GameStateGameplay(GameStateMachine* pGameStateMachine)
    : GameState{ pGameStateMachine }
    , m_pLevel{new Level}
    , m_pCurrentState{nullptr}
{
    StateChange(GameplayStateName::LOADING);
}

Level* GameStateGameplay::GetLevel()
{
    return m_pLevel;
}

void GameStateGameplay::Draw()
{
    m_pCurrentState->Draw();
}

bool GameStateGameplay::Update(bool processInput)
{
    return m_pCurrentState->Update(processInput);
}

void GameStateGameplay::StateChange(const GameplayStateName stateName)
{
    CurrentStateExit();
    switch (stateName)
    {
        case GameplayStateName::LOADING:
            m_pCurrentState = new GameplayStateLoading{ this };
            break;
    }
    m_pCurrentState->Enter();
}

void GameStateGameplay::CurrentStateExit()
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
    }
}