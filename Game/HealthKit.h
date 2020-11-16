#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class HealthKit : public PlaceableActor
        {
        public:
            HealthKit(int x, int y);
            virtual ActorType GetType() override;
            virtual void Draw() override;
        };
    }
}

