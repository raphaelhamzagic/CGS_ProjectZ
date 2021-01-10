#include <iostream>
#include <Windows.h>
#include "GameObject.h"

GameObject::GameObject(int x, int y, char symbol, GameObjectType type, Level* pLevel, GameObjectColor color)
    : m_active{ true }
    , m_x {x}
    , m_y{y}
    , m_symbol{symbol}
    , m_type{type}
    , m_pLevel{pLevel}
    , m_color{color}
{
}

void GameObject::Draw()
{
    if (m_active)
    {
        HANDLE console{ GetStdHandle(STD_OUTPUT_HANDLE) };
        COORD cursorPosition{ m_x, m_y };
        SetConsoleCursorPosition(console, cursorPosition);
        int color = static_cast<int>(m_color);
        SetConsoleTextAttribute(console, color);
        std::cout << m_symbol;
        color = static_cast<int>(GameObjectColor::Default);
        SetConsoleTextAttribute(console, color);
    }    
}

void GameObject::Update(bool processInput)
{
}

int GameObject::GetX()
{
    return m_x;
}

int GameObject::GetY()
{
    return m_y;
}
