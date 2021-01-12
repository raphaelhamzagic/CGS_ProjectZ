#include "Zombie.h"

#include <algorithm>
#include <vector>

#include "Level.h"
#include "Player.h"

Zombie::Zombie(int x, int y, Level* pLevel)
    : GameObject{ x, y, Zombie::kSymbol, GameObjectType::ZOMBIE, pLevel }
    , m_state{ZombieState::WANDERING}
    , m_updateCount{0}
{
}

void Zombie::Update(bool processInput)
{
    if (m_active && processInput)
    {
        m_symbol = kSymbol;
        if (m_state == ZombieState::WANDERING)
        {
            Wander();
        }
        else
        {
            Chase();
        }
    }    
}

void Zombie::Wander()
{
    ++m_updateCount;
    if (m_updateCount % kUpdateRatio == 0)
    {
        SetNextWanderingPosition();
        m_updateCount = 0;
    }
    m_color = kColor;
    if (GetPlayerDistance(m_x, m_y) <= kChasingDistance)
    {
        m_state = ZombieState::CHASING;
        m_updateCount = 0;
    }
}

void Zombie::Chase()
{
    ++m_updateCount;
    if (m_updateCount % kChasingUpdateRatio == 0)
    {
        SetNextChasingPosition();
    }
    m_color = kChasingColor;
    if (GetPlayerDistance(m_x, m_y) >= kStopChasingDistance)
    {
        m_state = ZombieState::WANDERING;
        m_updateCount = 0;
    }
}

void Zombie::SetNextChasingPosition()
{
    Player* pPlayer = m_pLevel->PlayerGet();
        
    int closestDistance = GetPlayerDistance(m_x, m_y);
    ZombiePosition closestPosition{m_x, m_y};
    std::vector<ZombiePosition> freePositions{};
    std::vector<ZombiePosition> positionsToCheck{
        ZombiePosition{m_x + 1, m_y},
        ZombiePosition{m_x - 1, m_y},
        ZombiePosition{m_x, m_y + 1},
        ZombiePosition{m_x, m_y - 1}
    };    
    std::vector<ZombiePosition>::const_iterator it;
    for (it = positionsToCheck.cbegin(); it != positionsToCheck.cend(); ++it)
    {
        ZombiePosition position = *it;
        GameObject* pGameObject = m_pLevel->GameObjectGet(position.x, position.y);
        if (pGameObject == nullptr || pGameObject->TypeGet() == GameObject::GameObjectType::PLAYER)
        {
            int distance = GetPlayerDistance(position.x, position.y);
            if (distance < closestDistance)
            {
                closestDistance = distance;
                closestPosition = position;
            }
        }
    }

    if (closestPosition.x == pPlayer->GetX() && closestPosition.y == pPlayer->GetY())
    {
        pPlayer->TakeDamage(0, 0, 1);
    }
    else
    {
        m_x = closestPosition.x;
        m_y = closestPosition.y;
    }    
}

void Zombie::SetNextWanderingPosition()
{   
    std::vector<ZombiePosition> freePositions{};
    std::vector<ZombiePosition> positionsToCheck{
        ZombiePosition{m_x + 1, m_y},
        ZombiePosition{m_x - 1, m_y},
        ZombiePosition{m_x, m_y + 1},
        ZombiePosition{m_x, m_y - 1}
    };
    std::vector<ZombiePosition>::const_iterator it;
    for (it = positionsToCheck.cbegin(); it != positionsToCheck.cend(); ++it)
    {
        ZombiePosition position = *it;
        GameObject* pGameObject = m_pLevel->GameObjectGet(position.x, position.y);
        if (pGameObject == nullptr)
        {
            freePositions.push_back(position);
        }
    }

    if (freePositions.size() > 0)
    {
        int randomPosition = rand() % freePositions.size();
        m_x = freePositions[randomPosition].x;
        m_y = freePositions[randomPosition].y;
    }
}

int Zombie::GetPlayerDistance(int x, int y)
{
    Player* pPlayer = m_pLevel->PlayerGet();    
    return (std::abs(pPlayer->GetX() - x) + std::abs(pPlayer->GetY() - y));
}