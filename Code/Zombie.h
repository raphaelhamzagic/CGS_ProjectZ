#pragma once
#include "GameObject.h"
#include <vector>

class Level;
class Zombie : public GameObject
{
    static constexpr char kSymbol = 'Z';
    static constexpr GameObjectColor kColor = GameObjectColor::Brown;
    static constexpr GameObjectColor kChasingColor = GameObjectColor::Red;
    
    enum class ZombieState
    {
        WANDERING,
        CHASING
    };
    ZombieState m_state;

    struct ZombiePosition {
        int x;
        int y;
    };
    

public:
    Zombie(int x, int y, Level* pLevel);
    virtual void Update(bool processInput) override;

private:
    void Chase();
    void Wander();
    void GetSurroundingPositions(std::vector<ZombiePosition> &positions);
};
