#pragma once
#include "GameObject.h"
#include <vector>

class Level;
class Zombie : public GameObject
{
    static constexpr char kSymbol = 'Z';
    static constexpr GameObjectColor kColor = GameObjectColor::Brown;
    static constexpr GameObjectColor kChasingColor = GameObjectColor::Red;
    static constexpr int kChasingDistance = 6;
    static constexpr int kStopChasingDistance = 10;
    static constexpr int kUpdateRatio = 2;
    static constexpr int kChasingUpdateRatio = 2;
        
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
    
    int m_updateCount;

public:
    Zombie(int x, int y, Level* pLevel);
    virtual void Update(bool processInput) override;

private:
    void Chase();
    void Wander();
    void SetNextChasingPosition();
    void SetNextWanderingPosition();
    int GetPlayerDistance(int x, int y);
};
