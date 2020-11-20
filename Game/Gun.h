#pragma once
#include "FireWeapon.h"

namespace projectz 
{
    namespace game 
    {
        class Gun : public FireWeapon
        {
        public:
            Gun(int x, int y, char symbol);
            virtual ActorType GetType() override;
        };
    }
}
