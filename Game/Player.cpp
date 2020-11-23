#include <iostream>
#include <vector>
#include <Windows.h>

#include "Ammo.h"
#include "Player.h"
#include "AudioManager.h"
#include "Key.h"
#include "MapChars.h"
#include "Point.h"
#include "FireWeapon.h"

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

        Player::Player(int x, int y, char aliveRightSymbol, char aliveLefSymbol, char aliveUpSymbol, char aliveDownSymbol, char deadSymbol)
            : PlaceableActor(x, y, aliveRightSymbol)
            , m_deadSymbol(deadSymbol)
            , m_pCurrentKey(nullptr)
            , m_lives(kStartingNumberOfLives)
            , m_hasGun(false)
            , m_pCurrentFireWeapon(nullptr)
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

        void Player::Draw(const HANDLE& console)
        {
            COORD playerCursorPosition;
            playerCursorPosition.X = m_pPosition->x;
            playerCursorPosition.Y = m_pPosition->y;
            SetConsoleCursorPosition(console, playerCursorPosition);

            int color = static_cast<int>(kPlayerColor[m_lives]);
            SetConsoleTextAttribute(console, color);
            char symbol;
            if (IsAlive())
            {
                if (m_pDirection->x == 1)
                {
                    symbol = MapChars::PlayerAliveRight;
                }
                else if (m_pDirection->x == -1)
                {
                    symbol = MapChars::PlayerAliveLeft;
                }
                else if (m_pDirection->y == 1)
                {
                    symbol = MapChars::PlayerAliveDown;
                }
                else
                {
                    symbol = MapChars::PlayerAliveUp;
                }
            }
            else
            {
                symbol = m_deadSymbol;
            }
            std::cout << symbol;
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
                return true;
            }
            else
            {
                AudioManager::GetInstance()->PlayDoorClosedSound();
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