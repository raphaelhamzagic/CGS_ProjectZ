#include "GunAmmo.h"

namespace projectz
{
    namespace game
    {
        static constexpr ActorColor kColor = ActorColor::White;
        static constexpr char kSymbol = '.';
        static constexpr int kAmount = 20;

        GunAmmo::GunAmmo(int x, int y)
            : Ammo(x, y, kColor, kSymbol, kAmount)
        {
        }
    }
}