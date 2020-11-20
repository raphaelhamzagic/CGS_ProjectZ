#include <iostream>
#include <Windows.h>
#include "HealthKit.h"

namespace projectz
{
    namespace game
    {
        HealthKit::HealthKit(int x, int y, char symbol, ActorColor color)
            : PlaceableActor(x, y, symbol, color)
        {
        }

        ActorType HealthKit::GetType()
        {
            return ActorType::HealthKit;;
        }

    }
}