#include <iostream>
#include <Windows.h>
#include "Zombie.h"
#include "Level.h"
#include "Point.h"

using namespace std;

namespace projectz {
    namespace game {

        static int constexpr kMovementOffset = 1;
        static int constexpr kChaseDistance = 4;
        static int constexpr kUpdateSpeed = 2;

        Zombie::Zombie(int x, int y, Level* pLevel)
            : PlaceableActor(x, y)
            , m_color(ActorColor::Brown)
            , m_isChasing(false)
            , m_chasingColor(ActorColor::Red)
            , m_updateControl(0)
            , m_pLevel(pLevel)
        {
        }

        void Zombie::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            int color = (m_isChasing) ? static_cast<int>(m_chasingColor) : static_cast<int>(m_color);
            SetConsoleTextAttribute(console, color);
            std::cout << 'z';
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        bool Zombie::Update(Level* pLevel, int playerX, int playerY)
        {
            bool hasCollided = false;
            if (m_IsActive)
            {
                ++m_updateControl;
                if (m_updateControl % kUpdateSpeed == 0)
                {
                    m_updateControl = 0;
                    Point newPosition;
                    if (m_isChasing)
                    {
                        newPosition = Chase(playerX, playerY);
                    }
                    else
                    {
                        double distanceToPlayer = m_pPosition->DistanceTo(playerX, playerY);
                        if (std::abs(distanceToPlayer) <= kChaseDistance)
                        {
                            m_isChasing = true;
                            newPosition = Chase(playerX, playerY);
                        }
                        else
                        {
                            newPosition = Wander();
                        }
                    }

                    if (!pLevel->IsWall(newPosition.x, newPosition.y) && !pLevel->IsDoor(newPosition.x, newPosition.y))
                    {
                        if (newPosition.x == playerX && newPosition.y == playerY)
                        {
                            hasCollided = true;
                        }
                        else
                        {
                            SetPosition(newPosition.x, newPosition.y);
                        }
                    }
                }
            }
            return hasCollided;
        }

        void Zombie::TakeDamage(const Point* pDamageDirection)
        {
            if (pDamageDirection)
            {
                int newPositionX = m_pPosition->x + pDamageDirection->x;
                int newPositionY = m_pPosition->y + pDamageDirection->y;
                if (!m_pLevel->IsWall(newPositionX, newPositionY) && !m_pLevel->IsDoor(newPositionX, newPositionY) && !m_pLevel->IsWindow(newPositionX, newPositionY))
                {
                    m_pPosition->x = newPositionX;
                    m_pPosition->y = newPositionY;
                }
            }
        }

        Point Zombie::Chase(int playerX, int playerY)
        {
            Point newPosition{ m_pPosition->x, m_pPosition->y };

            int diffX = playerX - m_pPosition->x;
            int diffY = playerY - m_pPosition->y;

            int directionX = 0;
            if (diffX > 0)
            {
                directionX = 1;
            }
            else if (diffX < 0)
            {
                directionX = -1;
            }
            int newPositionX = m_pPosition->x + directionX;

            int directionY = 0;
            if (diffY > 0)
            {
                directionY = 1;
            }
            else if (diffY < 0)
            {
                directionY = -1;
            }
            int newPositionY = m_pPosition->y + directionY;

            if (newPositionX != m_pPosition->x && newPositionY != m_pPosition->y)
            {
                int randomAxis = rand() % 2;
                if (randomAxis)
                {
                    newPosition.x = newPositionX;
                }
                else
                {
                    newPosition.y = newPositionY;
                }
            }
            else if (newPositionX != m_pPosition->x)
            {
                newPosition.x = newPositionX;
            }
            else if (newPositionY != m_pPosition->y)
            {
                newPosition.y = newPositionY;
            }

            return newPosition;
        }

        Point Zombie::Wander()
        {
            Point newPosition{ m_pPosition->x, m_pPosition->y };

            int randomAxis = rand() % 2;
            int randomDirection = ((rand() % 2)) ? 1 : -1;
            if (randomAxis)
            {
                newPosition.x = m_pPosition->x + (kMovementOffset * randomDirection);
            }
            else
            {
                newPosition.y = m_pPosition->y + (kMovementOffset * randomDirection);
            }

            return newPosition;
        }
    }
}
