#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Zombie : public PlaceableActor
        {
            static int s_count;
            int m_id;
            ActorColor m_color;

        public:
            Zombie(int x, int y);
            virtual ActorType GetType() override { return ActorType::Zombie; }
            virtual void Draw() override;
            virtual void Update(int playerX, int playerY) override;
        };
    }
}

