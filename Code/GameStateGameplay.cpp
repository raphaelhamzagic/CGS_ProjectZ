#include "GameStateGameplay.h"
#include "GameplayState.h"
#include "GameplayStateLoading.h"
#include "GameplayStatePlaying.h"
#include "Level.h"

GameStateGameplay::GameStateGameplay(GameStateMachine* pGameStateMachine)
    : GameState{ pGameStateMachine }
    , m_pLevel{new Level}
    , m_pState{nullptr}
{
    StateChange(GameplayStateName::LOADING);
}

Level* GameStateGameplay::LevelGet()
{
    return m_pLevel;
}

void GameStateGameplay::Draw()
{
    m_pState->Draw();
}

bool GameStateGameplay::Update(bool processInput)
{
    return m_pState->Update(processInput);
}

void GameStateGameplay::StateChange(const GameplayStateName stateName)
{
    StateExit();
    switch (stateName)
    {
        case GameplayStateName::LOADING:
            m_pState = new GameplayStateLoading{ this };
            break;
        case GameplayStateName::PLAYING:
            m_pState = new GameplayStatePlaying{ this };
            break;
    }
    m_pState->Enter();
}

void GameStateGameplay::StateExit()
{
    if (m_pState != nullptr)
    {
        m_pState->Exit();
        delete m_pState;
    }
}