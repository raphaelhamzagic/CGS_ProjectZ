#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class Zombie : public PlaceableActor
        {
        public:
            Zombie(int x, int y, char symbol);
            virtual ActorType GetType() override { return ActorType::Zombie; }
            virtual void Draw() override;
            bool Update(const int playerX, const int playerY, const std::vector<Point> &emptyPositionsAround);
            virtual void TakeDamage() override;

        private:
            bool m_isChasing;
            int m_wanderUpdateControl;
            int m_chaseUpdateControl;
            bool m_isHit;

            int GetDirection(const int value);
            bool Chase(int playerX, int playerY, const std::vector<Point>& emptyPositionsAround);
            Point GetRandomChasePosition(const int newPositionX, const int newPositionY, const std::vector<Point>& emptyPositionsAround);
            void Wander(const std::vector<Point>& emptyPositionsAround);
        };
    }
}

