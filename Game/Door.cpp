#include "Door.h"
#include <iostream>
#include <Windows.h>

namespace projectz {
    namespace game {

        Door::Door(int x, int y, ActorOrientation orientation, ActorColor color, ActorColor closedColor)
            : PlaceableActor(x, y, color)
            , m_orientation(orientation)
            , m_isOpen(false)
            , m_closedColor(closedColor)
        {
        }

        void Door::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            if (m_isOpen)
            {
                SetConsoleTextAttribute(console, (int)m_color);
            }
            else
            {
                SetConsoleTextAttribute(console, (int)m_closedColor);
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