#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Level;

        class Zombie : public PlaceableActor
        {
            static int constexpr kMovementOffset = 1;
            static int constexpr kChaseDistance = 3;

            bool m_isChasing;
            ActorColor m_chasingColor;          
            ActorColor m_color;

        public:
            Zombie(int x, int y);
            virtual ActorType GetType() override { return ActorType::Zombie; }
            virtual void Draw() override;
            virtual void Update(Level* level, int playerX, int playerY);
        private:
            Point Chase(int diffX, int diffY);
            Point Wander();
        };
    }
}

