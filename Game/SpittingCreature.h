#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class SpittingCreature : public PlaceableActor
        {
        public:
            SpittingCreature(int x, int y, char symbol);
            virtual ActorType GetType() override;
            bool Update(const int playerX, const int playerY, const std::vector<Point>& emptyPositionsAround);
        private:
            int GetDirection(const int value);
            void Shoot(const int playerX);
        };
    }
}
