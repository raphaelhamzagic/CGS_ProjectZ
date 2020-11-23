#include <iostream>
#include <Windows.h>

#include "Door.h"
#include "Point.h"

namespace projectz
{
    namespace game
    {
        Door::Door(int x, int y, char symbol, bool isLocked, ActorColor lockedColor, ActorColor unlockedColor)
            : PlaceableActor(x, y, symbol, lockedColor)
            , m_isLocked(isLocked)
            , m_unlockedColor(unlockedColor)
        {
        }

        void Door::Draw(const HANDLE& console)
        {
            COORD actorPosition;
            actorPosition.X = m_pPosition->x;
            actorPosition.Y = m_pPosition->y;
            SetConsoleCursorPosition(console, actorPosition);

            ActorColor color = m_isLocked ? m_color : m_unlockedColor;
            SetConsoleTextAttribute(console, (int)color);
            std::cout << m_symbol;
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }
    }
}