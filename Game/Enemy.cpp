#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
    : PlaceableActor(x, y)
    , m_currentMovementX(0)
    , m_currentMovementY(0)
    , m_directionX(0)
    , m_directionY(0)
    , m_movementInX(deltaX)
    , m_movementInY(deltaY)
{
    if (m_movementInX != 0)
    {
        m_directionX = 1;
    }
    if (m_movementInY != 0)
    {
        m_directionY = 1;
    }
}

void Enemy::Draw()
{
    std::cout << (char)153;
}

void Enemy::Update()
{
    if (m_movementInX != 0)
    {
        UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
    }
    if (m_movementInY != 0)
    {
        UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
    }
    SetPosition(m_pPosition->x + m_directionX, m_pPosition->y + m_directionY);
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
    if (direction != 0)
    {
        current += direction;
        if (std::abs(current) == movement)
        {
            direction *= -1;
        }
    }    
}

