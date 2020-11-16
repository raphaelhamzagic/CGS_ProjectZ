#include <iostream>
#include <Windows.h>

#include "Player.h"
#include "AudioManager.h"
#include "Key.h"
#include "Point.h"

using namespace std;

namespace projectz {
    namespace game {

        constexpr char kPlayerAliveSymbol = '@';
        constexpr char kPlayerDeadSymbol = 'X';
        constexpr int kStartingNumberOfLives = 3;
        const ActorColor kPlayerColor[] = {
            ActorColor::Red,
            ActorColor::Brown,
            ActorColor::Yellow,
            ActorColor::Green
        };

        Player::Player()
            : PlaceableActor(0, 0)
            , m_pCurrentKey(nullptr)
            , m_lives(kStartingNumberOfLives)
        {
            m_pDirection->x = 1;
            m_pDirection->y = 0;
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
                cout << kPlayerAliveSymbol;
            }
            else
            {
                cout << kPlayerDeadSymbol;
            }
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        void Player::TakeDamage(const Point* pDamageDirection)
        {
            if (m_lives > 0)
            {
                --m_lives;
            }
        }

        bool Player::IsAlive()
        {
            return m_lives > 0;
        }
    }
}