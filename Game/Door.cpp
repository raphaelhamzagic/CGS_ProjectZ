#include "Door.h"
#include <iostream>
#include <Windows.h>

namespace projectz {
    namespace game {

        Door::Door(int x, int y, ActorOrientation orientation, bool isLocked, ActorColor unlockedColor, ActorColor lockedColor)
            : PlaceableActor(x, y, lockedColor)
            , m_orientation(orientation)
            , m_isLocked(isLocked)
            , m_unlockedColor(unlockedColor)
        {
        }

        void Door::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            if (m_isLocked)
            {
                SetConsoleTextAttribute(console, (int)m_color);
            }
            else
            {
                SetConsoleTextAttribute(console, (int)m_unlockedColor);
            }
            if (m_orientation == ActorOrientation::Horizontal)
            {
                std::cout << (char)205;
            }
            else
            {
                std::cout << (char)186;
            }
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }
    }
}