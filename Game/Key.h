#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class Key : public PlaceableActor
        {
        public:
            Key(int x, int y, char symbol, ActorColor color)
                : PlaceableActor(x, y, symbol, color)
            {
            }
            virtual ActorType GetType() override { return ActorType::Key; }
        };
    }
}