#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class FireWeapon : public PlaceableActor
        {
        public:
            FireWeapon(int x, int y, ActorColor color, char symbol,  int ammo, int damage, int bulletsPerShot);
            virtual void Draw() override;
            virtual int GetAmmo();
            virtual void AddAmmo(int amount);

            virtual int GetDamage();
            virtual void Shoot();

        private:
            char m_symbol;
            int m_ammo;
            int m_damage;
            int m_bulletsPerShot;
        };
    }
}

