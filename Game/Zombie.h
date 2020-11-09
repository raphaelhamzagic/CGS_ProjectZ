#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Level;

        class Zombie : public PlaceableActor
        {
            bool m_isChasing;
            ActorColor m_chasingColor;

            int m_updateControl;
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

