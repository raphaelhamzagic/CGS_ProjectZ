#pragma once
class State
{
public:
    virtual void Enter();
    virtual void Exit();
    virtual void Draw() = 0;
    virtual bool Update(bool processInput) = 0;
};