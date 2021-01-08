#include "Player.h"

#include <conio.h>

#include "Keyboard.h"
#include "Level.h"


Player::Player(int x, int y)
    : GameObject{ x, y, Player::kGoingRightSymbol, GameObjectType::PLAYER }
{
}

void Player::Update(bool processInput, Level* pLevel)
{
    if (processInput)
    {
        int x = m_x;
        int y = m_y;

        int input = _getch();
        int arrowInput{};

        if (input == Keyboard::Arrow)
        {
            arrowInput = _getch();
        }

        if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowUp) || ((char)input == 'W' || (char)input == 'w'))
        {
            --y;
            m_mainSymbol = kGoingUpSymbol;
        }
        else if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowDown) || ((char)input == 'S' || (char)input == 's'))
        {
            ++y;
            m_mainSymbol = kGoingDownSymbol;
        }
        else if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowRight) || ((char)input == 'D' || (char)input == 'd'))
        {
            ++x;
            m_mainSymbol = kGoingRightSymbol;
        }
        else if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowLeft) || ((char)input == 'A' || (char)input == 'a'))
        {
            --x;
            m_mainSymbol = kGoingLeftSymbol;
        }

        GameObject* gameObject = pLevel->GameObjectGet(x, y);
        if (gameObject != nullptr)
        {

        }
        else
        {
            m_x = x;
            m_y = y;
        }
    }
}
