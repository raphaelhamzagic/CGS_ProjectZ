#pragma once

class State;

class StateMachine
{
public:
    virtual bool UpdateState(bool processInput = true);
    virtual void DrawCurrentState();
    virtual void ChangeState(State* pNewState);

private:
    State* m_pCurrentState;
};