#include "Game.h"
#include "GameStateMachine.h"


Game::Game()
    : m_stateMachine{ new GameStateMachine{} }
{
    m_stateMachine->ChangeState(GameStateMachine::GameStateName::MAIN_MENU);
}

void Game::Loop()
{
    bool leaveGameLoop{};
    do {
        m_stateMachine->UpdateCurrentState(false);
        m_stateMachine->DrawCurrentState();
        leaveGameLoop = m_stateMachine->UpdateCurrentState(true);
    } 
    while (!leaveGameLoop);
}

Game::~Game()
{
    delete m_stateMachine;
    m_stateMachine = nullptr;
}
