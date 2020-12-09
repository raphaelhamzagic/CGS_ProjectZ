#include "Game.h"
#include "GameStateMachine.h"


Game::Game()
    : m_stateMachine{ new GameStateMachine{} }
{
    m_stateMachine->ChangeState(GameStateMachine::GameState::MAIN_MENU);
}

void Game::Loop()
{
    bool loop{};
    do {
        m_stateMachine->UpdateState(false);
        m_stateMachine->DrawCurrentState();
        loop = m_stateMachine->UpdateState(true);
    } 
    while (loop);
}

Game::~Game()
{
    delete m_stateMachine;
    m_stateMachine = nullptr;
}
