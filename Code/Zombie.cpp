#include "Zombie.h"

#include <algorithm>
#include <vector>

#include "Level.h"

Zombie::Zombie(int x, int y, Level* pLevel)
    : GameObject{ x, y, Zombie::kSymbol, GameObjectType::ZOMBIE, pLevel }
    , m_state{ZombieState::WANDERING}
{
}

void Zombie::Update(bool processInput)
{
    if (m_active)
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

void Zombie::Chase()
{
    m_color = kChasingColor;
}

void Zombie::Wander()
{
    std::vector<ZombiePosition> positions{};
    GetSurroundingPositions(positions);
    int randomPosition = rand() % positions.size();
    ZombiePosition position = positions[randomPosition];
    m_x = position.x;
    m_y = position.y;

    m_color = kColor;
}

void Zombie::GetSurroundingPositions(std::vector<ZombiePosition> &positions)
{
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
            positions.push_back(position);
        }
    }
}