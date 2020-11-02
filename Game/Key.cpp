#include "Key.h"
#include <iostream>
#include <Windows.h>

namespace projectz {
    namespace game {

        void Key::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)m_color);

            std::cout << "k";
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

    }
}