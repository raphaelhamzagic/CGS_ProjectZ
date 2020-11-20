#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class FireWeapon : public PlaceableActor
        {
        public:
            FireWeapon(int x, int y, char symbol, ActorColor color, int ammo, int damage, int bulletsPerShot);
            virtual int GetAmmo();
            virtual void AddAmmo(int amount);

            virtual int GetDamage();
            virtual void Shoot();

        private:
            int m_ammo;
            int m_damage;
            int m_bulletsPerShot;
        };
    }
}

