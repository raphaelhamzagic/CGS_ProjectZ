#include "Gun.h"
#include "FireWeapon.h"

namespace projectz
{
    namespace game
    {
        static ActorColor constexpr kColor = ActorColor::White;
        static int constexpr kAmmo = 5;
        static int constexpr kDamage = 1;
        static constexpr int kBulletsPerShot = 1;

        Gun::Gun(int x, int y, char symbol)
            : FireWeapon(x, y, symbol, kColor, kAmmo, kDamage, kBulletsPerShot)
        {
        }

        ActorType Gun::GetType()
        {
            return ActorType::Gun;
        }        
    }
}