#pragma once
class State
{
public:
    virtual void Enter();
    virtual bool Update(bool processInput);
    virtual void Draw();
    virtual void Exit();
};