#include "GunAmmo.h"

namespace projectz
{
    namespace game
    {
        static constexpr ActorColor kColor = ActorColor::White;
        static constexpr int kAmount = 20;

        GunAmmo::GunAmmo(int x, int y, char symbol)
            : Ammo(x, y, symbol, kColor, kAmount)
        {
        }
    }
}