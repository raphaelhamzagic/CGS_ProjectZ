#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class Key : public PlaceableActor
        {
        public:
            Key(int x, int y, ActorColor color)
                : PlaceableActor(x, y, color)
            {
            }
            virtual ActorType GetType() override { return ActorType::Key; }
            virtual void Draw() override;
        };
    }
}