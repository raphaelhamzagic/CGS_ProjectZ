#pragma once

class State;

class StateMachine
{
public:
    virtual void DrawCurrentState();
    virtual void ChangeState(State* pNewState);
    virtual bool UpdateCurrentState(bool processInput = true);

private:
    State* m_pCurrentState;
};