#pragma once
#include "GameObject.h"

class Level;
class Player : public GameObject
{
    static constexpr char kGoingRightSymbol = '>';
    static constexpr char kGoingLeftSymbol = '<';
    static constexpr char kGoingUpSymbol = '^';
    static constexpr char kGoingDownSymbol = 'v';
    static constexpr char kDeadSymbol = 'X';

    static constexpr int kInitialHealth = 3;

public:
    Player(int x, int y, Level* pLevel);
    virtual void Update(bool processInput) override;
    virtual void TakeDamage(int directionX, int directionY, int damage) override;
    bool IsAlive();
};

