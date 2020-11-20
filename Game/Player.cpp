#include <iostream>
#include <vector>
#include <Windows.h>

#include "Ammo.h"
#include "Player.h"
#include "AudioManager.h"
#include "Key.h"
#include "Point.h"
#include "FireWeapon.h"

using namespace std;

namespace projectz 
{
    namespace game
    {        
        constexpr int kStartingNumberOfLives = 3;

        const ActorColor kPlayerColor[] = {
            ActorColor::Red,
            ActorColor::Brown,
            ActorColor::Yellow,
            ActorColor::Green
        };

        Player::Player(int x, int y, char aliveSymbol, char deadSymbol)
            : PlaceableActor(x, y, aliveSymbol)
            , m_deadSymbol(deadSymbol)
            , m_pCurrentKey(nullptr)
            , m_lives(kStartingNumberOfLives)
            , m_hasGun(false)
        {
        }

        bool Player::HasKey()
        {
            return m_pCurrentKey != nullptr;
        }

        bool Player::HasKey(ActorColor color)
        {
            return HasKey() && m_pCurrentKey->GetColor() == color;
        }

        void Player::PickupKey(Key* key)
        {
            m_pCurrentKey = key;
        }

        void Player::UseKey()
        {
            m_pCurrentKey->Remove();
            m_pCurrentKey = nullptr;
        }

        void Player::DropKey()
        {
            if (m_pCurrentKey)
            {
                m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
                m_pCurrentKey = nullptr;
                AudioManager::GetInstance()->PlayKeyDropSound();
            }
        }

        void Player::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            int color = static_cast<int>(kPlayerColor[m_lives]);
            SetConsoleTextAttribute(console, color);
            if (IsAlive())
            {
                cout << m_symbol;
            }
            else
            {
                cout << m_deadSymbol;
            }
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        void Player::TakeDamage()
        {
            if (m_lives > 0)
            {
                --m_lives;
            }
        }

        void Player::PickupGun(FireWeapon* gun)
        {
            m_hasGun = true;
            m_pCurrentFireWeapon = gun;
        }

        bool Player::HasGun()
        {
            return m_hasGun;
        }

        int Player::GetAmmo()
        {
            if (m_pCurrentFireWeapon != nullptr)
            {
                return m_pCurrentFireWeapon->GetAmmo();
            }
            return 0;
        }

        bool Player::ShootFireWeapon()
        {
            if (m_pCurrentFireWeapon != nullptr && GetAmmo() > 0)
            {
                AudioManager::GetInstance()->PlayGunShootingSound();
                m_pCurrentFireWeapon->Shoot();
            }
            else
            {
                return false;
            }
        }

        void Player::PickupGunAmmo(Ammo* ammo)
        {
            if (m_pCurrentFireWeapon != nullptr)
            {
                m_pCurrentFireWeapon->AddAmmo(ammo->GetAmount());
            }
        }

        void Player::PickupHealthKit()
        {
            if (m_lives < 3)
            {
                ++m_lives;
            }
        }

        bool Player::IsAlive()
        {
            return m_lives > 0;
        }
    }
}