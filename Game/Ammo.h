#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class Ammo : public PlaceableActor
        {
        public:
            Ammo(int x, int y, ActorColor color, char symbol, int amount);
            virtual ActorType GetType() override;
            virtual void Draw() override;
            virtual int GetAmount();

        private:
            int m_amount;
            char m_symbol;
        };
    }
}

