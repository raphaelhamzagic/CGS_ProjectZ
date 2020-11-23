#include <algorithm>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "Zombie.h"
#include "Point.h"

namespace projectz
{
    namespace game
    {
        static ActorColor constexpr kColor = ActorColor::Brown;
        static ActorColor constexpr kChasingColor = ActorColor::Red;
        
        static int constexpr kChaseDistance = 6;
        static int constexpr kWanderUpdateSpeed = 2;
        static int constexpr kChaseUpdateSpeed = 2;

        Zombie::Zombie(int x, int y, char symbol)
            : PlaceableActor(x, y, symbol, kColor)
            , m_isChasing(false)
            , m_wanderUpdateControl(0)
            , m_chaseUpdateControl(0)
            , m_isHit(false)
        {
        }

        void Zombie::Draw(const HANDLE& console)
        {
            COORD actorPosition;
            actorPosition.X = m_pPosition->x;
            actorPosition.Y = m_pPosition->y;
            SetConsoleCursorPosition(console, actorPosition);

            int color = (m_isChasing) ? static_cast<int>(kChasingColor) : static_cast<int>(m_color);
            SetConsoleTextAttribute(console, color);
            std::cout << m_symbol;
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        bool Zombie::Update(const int playerX, const int playerY, const std::vector<Point> &emptyPositionsAround)
        {
            bool hasHitPlayer = false;
            if (m_isHit)
            {
                m_isHit = false;
            }
            else
            {
                if (m_isActive)
                {
                    if (m_isChasing)
                    {
                        ++m_chaseUpdateControl;
                        if (m_chaseUpdateControl % kChaseUpdateSpeed == 0)
                        {
                            m_chaseUpdateControl = 0;
                            hasHitPlayer = Chase(playerX, playerY, emptyPositionsAround);
                        }
                    }
                    else
                    {
                        ++m_wanderUpdateControl;
                        if (m_wanderUpdateControl % kWanderUpdateSpeed == 0)
                        {
                            m_wanderUpdateControl = 0;
                            double distanceToPlayer = m_pPosition->DistanceTo(playerX, playerY);
                            if (std::abs(distanceToPlayer) <= kChaseDistance)
                            {
                                m_isChasing = true;
                                hasHitPlayer = Chase(playerX, playerY, emptyPositionsAround);
                            }
                            else
                            {
                                Wander(emptyPositionsAround);
                            }
                        }
                    }
                }
            }         
            return hasHitPlayer;
        }

        void Zombie::TakeDamage()
        {
            m_isHit = true;
        }

        bool Zombie::Chase(int playerX, int playerY, const std::vector<Point> &emptyPositionsAround)
        {
            int diffX = playerX - m_pPosition->x;
            int directionX = GetDirection(diffX);
            int newPositionX = m_pPosition->x + directionX;

            int diffY = playerY - m_pPosition->y;
            int directionY = GetDirection(diffY);
            int newPositionY = m_pPosition->y + directionY;

            Point newPosition = GetRandomChasePosition(newPositionX, newPositionY, emptyPositionsAround);
            if (newPosition.x == playerX && newPosition.y == playerY)
            {
                return true;
            }
            else if (newPosition.x != m_pPosition->x || newPosition.y != m_pPosition->y)
            {
               SetPosition(newPosition.x, newPosition.y);
            }
            return false;         
        }

        Point Zombie::GetRandomChasePosition(const int newPositionX, const int newPositionY, const std::vector<Point> &emptyPositionsAround)
        {
            Point newPosition{ m_pPosition->x , m_pPosition->y };
            Point p{};

            if (newPositionX != m_pPosition->x && newPositionY != m_pPosition->y)
            {                
                int axis = rand() % 2;
                if (axis)
                {
                    p.x = newPositionX;
                    p.y = m_pPosition->y;
                }
                else
                {
                    p.x = m_pPosition->x;
                    p.y = newPositionY;
                }
                auto found = std::find(emptyPositionsAround.begin(), emptyPositionsAround.end(), p);
                if (found == emptyPositionsAround.end())
                {
                    axis = (axis == 1) ? 0 : 1;
                    if (axis)
                    {
                        p.x = newPositionX;
                        p.y = m_pPosition->y;
                    }
                    else
                    {
                        p.x = m_pPosition->x;
                        p.y = newPositionY;
                    }
                    found = std::find(emptyPositionsAround.begin(), emptyPositionsAround.end(), p);
                    if (found != emptyPositionsAround.end())
                    {
                        newPosition = p;
                    }
                }
                else
                {
                    newPosition = p;
                }
            }
            else {
                if (newPositionX != m_pPosition->x)
                {
                    p.x = newPositionX;
                    p.y = m_pPosition->y;
                }
                else if (newPositionY != m_pPosition->y)
                {
                    p.x = m_pPosition->x;
                    p.y = newPositionY;
                }
                if (p.x || p.y)
                {
                    auto found = std::find(emptyPositionsAround.begin(), emptyPositionsAround.end(), p);
                    if (found != emptyPositionsAround.end())
                    {
                        newPosition = p;
                    }
                }
            }

            return newPosition;
        }

        int Zombie::GetDirection(const int value)
        {
            int direction{};
            if (value > 0)
            {
                direction = 1;
            }
            else if (value < 0)
            {
                direction = -1;
            }
            return direction;
        }

        void Zombie::Wander(const std::vector<Point>& emptyPositionsAround)
        {
            Point newPosition{ m_pPosition->x, m_pPosition->y };
            if (emptyPositionsAround.size() > 0)
            {
                int randomPosition = rand() % emptyPositionsAround.size();
                newPosition = emptyPositionsAround.at(randomPosition);
                SetPosition(newPosition.x, newPosition.y);
            }            
        }
    }
}
