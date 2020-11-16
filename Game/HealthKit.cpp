#include <iostream>
#include <Windows.h>
#include "HealthKit.h"

namespace projectz
{
    namespace game
    {
        static constexpr ActorColor kColor = ActorColor::LightGreen;
        static constexpr char kSymbol = '+';

        HealthKit::HealthKit(int x, int y)
            : PlaceableActor(x, y, kColor)
        {
        }

        ActorType HealthKit::GetType()
        {
            return ActorType::HealthKit;;
        }

        void HealthKit::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)m_color);
            std::cout << kSymbol;
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
 
        }
    }
}