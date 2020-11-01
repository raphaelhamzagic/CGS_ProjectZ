#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

namespace projectz {
    namespace game {

        constexpr int kStartingNumberOfLives = 3;
        constexpr char kPlayerSymbol = '@';

        Player::Player()
            : PlaceableActor(0, 0)
            , m_pCurrentKey(nullptr)
            , m_money(0)
            , m_lives(kStartingNumberOfLives)
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
            cout << '@';
        }
    }
}