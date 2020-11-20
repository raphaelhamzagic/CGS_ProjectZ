#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class HealthKit : public PlaceableActor
        {
        public:
            HealthKit(int x, int y, char symbol, ActorColor color);
            virtual ActorType GetType() override;
        };
    }
}

