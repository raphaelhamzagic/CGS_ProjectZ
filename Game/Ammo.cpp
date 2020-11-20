#include <iostream>
#include <Windows.h>
#include "Ammo.h"

namespace projectz
{
    namespace game
    {
        Ammo::Ammo(int x, int y, char symbol, ActorColor color, int amount)
            : PlaceableActor(x, y, symbol, color)
            , m_amount(amount)
        {
        }

        ActorType Ammo::GetType()
        {
            return ActorType::GunAmmo;
        }

        int Ammo::GetAmount()
        {
            return m_amount;
        }
    }
}