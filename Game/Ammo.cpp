#include <iostream>
#include <Windows.h>
#include "Ammo.h"

namespace projectz
{
    namespace game
    {
        Ammo::Ammo(int x, int y, ActorColor color, char symbol, int amount)
            : PlaceableActor(x, y, color)
            , m_symbol(symbol)
            , m_amount(amount)
        {
        }

        ActorType Ammo::GetType()
        {
            return ActorType::GunAmmo;
        }

        int Ammo::GetAmount()
        {
            return m_amount;
        }

        void Ammo::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)m_color);
            std::cout << m_symbol;
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }
    }
}