#include <iostream>
#include <Windows.h>
#include "FireWeapon.h"

namespace projectz 
{
    namespace game
    {
        FireWeapon::FireWeapon(int x, int y, char symbol, ActorColor color, int ammo, int damage, int bulletsPerShot)
            : PlaceableActor(x, y, symbol, color)
            , m_ammo(ammo)
            , m_damage(damage)
            , m_bulletsPerShot(bulletsPerShot)
        {
        }

        int FireWeapon::GetAmmo()
        {
            return m_ammo;
        }

        void FireWeapon::AddAmmo(int amount)
        {
            m_ammo += amount;
        }

        int FireWeapon::GetDamage()
        {
            return m_damage;
        }

        void FireWeapon::Shoot()
        {
            if (m_ammo >= m_bulletsPerShot)
            {
                m_ammo -= m_bulletsPerShot;
            }
        }
    }
}
