#include <algorithm>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "SpittingCreature.h"
#include "GameplayState.h"
#include "Point.h"

namespace projectz
{
    namespace game
    {
        struct SpittingCreatureProjectile
        {
            Point position;
            int directionX;
        };

        static int constexpr kShootingMaxInterval = 2;
        static int constexpr kRecoveringMaxInterval = 3;

        SpittingCreature::SpittingCreature (int x, int y, char symbol, char projectileSymbol, int shootingDirectionX)
            : PlaceableActor(x, y, symbol)
            , m_projectileSymbol(projectileSymbol)
            , m_state(State::STATE_AIMING)
            , m_shootingInterval(0)
            , m_recoveringInterval(0)
        {
            if (shootingDirectionX == -1)
            {
                m_shootingDirectionX = -1;
            }
            else
            {
                m_shootingDirectionX = 1;
            }
        }

        SpittingCreature::~SpittingCreature()
        {
            while (!m_projectiles.empty())
            {
                delete m_projectiles.back();
                m_projectiles.pop_back();
            }
        }

        ActorType SpittingCreature::GetType()
        {
            return ActorType::SpittingCreature;
        }

        bool SpittingCreature::Update(const int playerX, const int playerY, GameplayState* pOwner)
        {
            bool hasHitPlayer = false;
            if (m_isActive)
            {
                if (!m_projectiles.empty())
                {
                    hasHitPlayer = UpdateProjectiles(playerX, playerY, pOwner);
                }

                if (m_state == State::STATE_RECOVERING)
                {
                    ++m_recoveringInterval;
                    if (m_recoveringInterval % kRecoveringMaxInterval == 0)
                    {
                        m_recoveringInterval = 0;
                        UpdateCreature(playerX, playerY, pOwner);
                    }
                }
                else
                {
                    UpdateCreature(playerX, playerY, pOwner);
                }                        
            }
            return hasHitPlayer;
        }

        
        void SpittingCreature::UpdateCreature(const int playerX, const int playerY, GameplayState* pOwner)
        {
            int diffX = playerX - m_pPosition->x;
            int directionX = GetDirection(diffX);
            int diffY = playerY - m_pPosition->y;
            int directionY = GetDirection(diffY);
            if (directionY == 0 && directionX == m_shootingDirectionX)
            {
                Shoot(playerX);
            }
            else
            {
                if (directionX == m_shootingDirectionX)
                {
                    m_state = State::STATE_AIMING;
                    int newPositionX = m_pPosition->x;
                    int newPositionY = m_pPosition->y + directionY;
                    if (pOwner->IsPositionEmpty(newPositionX, newPositionY))
                    {
                        SetPosition(newPositionX, newPositionY);
                    }
                }
                else
                {
                    m_state = State::STATE_STOPPED;
                }
            }
        }


        int SpittingCreature::GetDirection(const int value)
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

        void SpittingCreature::Shoot(const int playerX)
        {
            ++m_shootingInterval;
            if (m_shootingInterval % kShootingMaxInterval == 0)
            {
                m_shootingInterval = 0;
                m_state = State::STATE_SHOOTING;
                int diffX = playerX - m_pPosition->x;
                int directionX = GetDirection(diffX);
                m_projectiles.push_back(
                    new SpittingCreatureProjectile{
                        Point {m_pPosition->x + directionX, m_pPosition->y},
                        directionX
                    }
                );
            }            
        }

        bool SpittingCreature::UpdateProjectiles(const int playerX, const int playerY, GameplayState* pOwner)
        {
            bool hasHitPlayer = false;
            for (auto it{ m_projectiles.begin() }; it != m_projectiles.end(); ) {
                SpittingCreatureProjectile* pProjectile = *it;
                int newX = pProjectile->position.x + pProjectile->directionX;
                int newY = pProjectile->position.y;
                if (newX == playerX && newY == playerY)
                {
                    hasHitPlayer = true;
                    it = m_projectiles.erase(it);
                }
                else
                {
                    if (pOwner->IsPositionEmpty(newX, newY))
                    {
                        PlaceableActor* actor = pOwner->GetActorAtPosition(newX, newY);
                        if (actor != nullptr)
                        {
                            it = m_projectiles.erase(it);
                        }
                        else
                        {
                            pProjectile->position.x = newX;
                            ++it;
                        }
                    }
                    else
                    {
                        it = m_projectiles.erase(it);
                    }
                }                
            }
            return hasHitPlayer;
        }

        void SpittingCreature::Draw(const HANDLE& console)
        {
            COORD actorPosition;
            
            actorPosition.X = m_pPosition->x;
            actorPosition.Y = m_pPosition->y;
            SetConsoleCursorPosition(console, actorPosition);

            ActorColor color = ActorColor::Yellow;
            switch (m_state)
            {
                case State::STATE_AIMING:
                    color = ActorColor::Brown;
                    break;
                case State::STATE_RECOVERING:
                    color = ActorColor::Red;
                    break;
                case State::STATE_SHOOTING:
                    color = ActorColor::LightRed;
                    break;
            }
            SetConsoleTextAttribute(console, static_cast<int>(color));
            std::cout << m_symbol;

            for (auto it{ m_projectiles.begin() }; it != m_projectiles.end(); ++it) {
                SpittingCreatureProjectile* pProjectile = *it;
                actorPosition.X = pProjectile->position.x;
                actorPosition.Y = pProjectile->position.y;
                SetConsoleCursorPosition(console, actorPosition);
                SetConsoleTextAttribute(console, static_cast<int>(m_color));
                std::cout << m_projectileSymbol;
            }

            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        void SpittingCreature::TakeDamage()
        {
            m_state = State::STATE_RECOVERING;
            m_recoveringInterval = 0;
        }
    }
}