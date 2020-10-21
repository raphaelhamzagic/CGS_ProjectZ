#include "Key.h"
#include <iostream>
#include <Windows.h>

void Key::Draw()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (int)m_color);

    std::cout << "+";
    SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
