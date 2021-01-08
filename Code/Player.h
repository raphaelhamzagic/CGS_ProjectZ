#pragma once
#include "GameObject.h"

class Level;
class Player : public GameObject
{
    static char constexpr kGoingRightSymbol = '>';
    static char constexpr kGoingLeftSymbol = '<';
    static char constexpr kGoingUpSymbol = '^';
    static char constexpr kGoingDownSymbol = 'v';
    static char constexpr kDeadSymbol = 'X';

public:
    Player(int x, int y);
    virtual void Update(bool processInput, Level* pLevel) override;
};

