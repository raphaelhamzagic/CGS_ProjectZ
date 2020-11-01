#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Goal : public PlaceableActor
        {
        public:
            Goal(int x, int y);
            virtual ActorType GetType() override { return ActorType::Goal; }
            virtual void Draw() override;
        };
    }
}