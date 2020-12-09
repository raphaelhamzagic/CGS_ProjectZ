#pragma once
#include "State.h"
class GameStateMainMenu : public State
{
public:
    virtual bool Update(bool processInput) override;
    virtual void Draw() override;
};

