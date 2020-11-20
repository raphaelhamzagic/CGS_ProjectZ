#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class Ammo : public PlaceableActor
        {
        public:
            Ammo(int x, int y, char symbol, ActorColor color, int amount);
            virtual ActorType GetType() override;
            virtual int GetAmount();
        private:
            int m_amount;
        };
    }
}

