#include "Zombie.h"
#include <iostream>
#include <Windows.h>
#include "Level.h"

using namespace std;

namespace projectz {
    namespace game {

        static int constexpr kMovementOffset = 1;
        static int constexpr kChaseDistance = 3;
        static int constexpr kUpdateSpeed = 2;

        Zombie::Zombie(int x, int y)
            : PlaceableActor(x, y)
            , m_color(ActorColor::Brown)
            , m_isChasing(false)
            , m_chasingColor(ActorColor::Red)
            , m_updateControl(0)        
        {
        }

        void Zombie::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            if (m_isChasing)
            {
                SetConsoleTextAttribute(console, (int)m_chasingColor);
            }
            else
            {
                SetConsoleTextAttribute(console, (int)m_color);
            }
            std::cout << 'z';
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        void Zombie::Update(Level* pLevel, int playerX, int playerY)
        {
            if (m_IsActive)
            {
                ++m_updateControl;
                if (m_updateControl % kUpdateSpeed == 0)
                {
                    m_updateControl = 0;

                    double distanceToPlayer = m_pPosition->DistanceTo(playerX, playerY);
                    Point newPosition;
                    if (std::abs(distanceToPlayer) <= kChaseDistance)
                    {
                        newPosition = Chase(playerX, playerY);
                        m_isChasing = true;
                    }
                    else
                    {
                        newPosition = Wander();
                        m_isChasing = false;
                    }
                    if (!pLevel->IsWall(newPosition.x, newPosition.y) && !pLevel->IsDoor(newPosition.x, newPosition.y))
                    {
                        SetPosition(newPosition.x, newPosition.y);
                    }
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
