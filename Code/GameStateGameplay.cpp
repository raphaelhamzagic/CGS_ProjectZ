#include "GameStateGameplay.h"
#include "GameplayState.h"

#include "Level.h"

GameStateGameplay::GameStateGameplay(GameStateMachine* pGameStateMachine)
    : GameState{ pGameStateMachine }
    , m_pLevel{new Level}
    , m_state{GameplayState::LOADING}
{
}

Level* GameStateGameplay::LevelGet()
{
    return m_pLevel;
}

bool GameStateGameplay::PlayingStateUpdate(bool processInput)
{
    return m_pLevel->Update(processInput);
}

void GameStateGameplay::PlayingStateDraw()
{
    system("cls");
    m_pLevel->Draw();
}

void GameStateGameplay::Draw()
{
    switch (m_state)
    {
        case GameplayState::LOADING:
            system("cls");
            std::cout << "Loading..." << std::endl;
            break;

        case GameplayState::PLAYING:
            PlayingStateDraw();
            break;
    }
}

bool GameStateGameplay::Update(bool processInput)
{
    bool leaveMainGameLoop { false };
    switch (m_state)
    {
        case GameplayState::LOADING:
        {
            m_pLevel->Load("Map/2.txt");
            m_state = GameplayState::PLAYING;
            break;
        }
        case GameplayState::PLAYING:
            leaveMainGameLoop = PlayingStateUpdate(processInput);
            break;
    }
    return leaveMainGameLoop;
}

void GameStateGameplay::Lose()
{
    m_state = GameplayState::LOADING;
}
