#pragma once

class State;

class StateMachine
{
public:
    virtual void DrawCurrentState();
    virtual void ChangeState(State* pNewState);
    virtual bool UpdateCurrentState(bool processInput = true);

protected:
    State* m_pCurrentState;
};