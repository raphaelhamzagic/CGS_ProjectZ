#include <iostream>
#include <Windows.h>
#include "GameObject.h"

GameObject::GameObject(int x, int y, char mainSymbol, GameObjectType type, GameObjectColor mainColor)
    : m_x{x}
    , m_y{y}
    , m_mainSymbol{mainSymbol}
    , m_type{type}
    , m_mainColor{mainColor}
{
}

void GameObject::Draw()
{
    HANDLE console{};
    COORD cursorPosition{ m_x, m_y };
    SetConsoleCursorPosition(console, cursorPosition);
    int color = static_cast<int>(m_mainColor);
    SetConsoleTextAttribute(console, color);
    std::cout << m_mainSymbol;
    color = static_cast<int>(GameObjectColor::Default);
    SetConsoleTextAttribute(console, color);
}

void GameObject::Update(bool processInput)
{
}
