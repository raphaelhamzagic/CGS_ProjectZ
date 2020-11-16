#include <iostream>
#include <Windows.h>
#include "FireWeapon.h"

namespace projectz 
{
    namespace game
    {
        FireWeapon::FireWeapon(int x, int y, ActorColor color, char symbol, int ammo, int damage, int bulletsPerShot)
            : PlaceableActor(x, y, color)
            , m_symbol(symbol)
            , m_ammo(ammo)
            , m_damage(damage)
            , m_bulletsPerShot(bulletsPerShot)
        {
        }

        void FireWeapon::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)m_color);
            std::cout << m_symbol;
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
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
