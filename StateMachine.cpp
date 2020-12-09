#include "StateMachine.h"
#include "State.h"

void StateMachine::DrawCurrentState()
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Draw();
    }
}

void StateMachine::ChangeState(State* pNewState)
{
    if (m_pCurrentState != nullptr)
    {
        m_pCurrentState->Exit();
    }
    m_pCurrentState = pNewState;
    m_pCurrentState->Enter();
}

bool StateMachine::UpdateCurrentState(bool processInput)
{
    if (m_pCurrentState != nullptr)
    {
        return m_pCurrentState->Update(processInput);
    }
    return false;
}