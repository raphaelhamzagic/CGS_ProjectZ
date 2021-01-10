#include "Player.h"

#include <conio.h>

#include "Keyboard.h"
#include "Level.h"


Player::Player(int x, int y, Level* pLevel)
    : GameObject{ x, y, Player::kGoingRightSymbol, GameObjectType::PLAYER, pLevel }
{
}

void Player::Update(bool processInput)
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
            m_symbol = kGoingUpSymbol;
        }
        else if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowDown) || ((char)input == 'S' || (char)input == 's'))
        {
            ++y;
            m_symbol = kGoingDownSymbol;
        }
        else if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowRight) || ((char)input == 'D' || (char)input == 'd'))
        {
            ++x;
            m_symbol = kGoingRightSymbol;
        }
        else if ((input == Keyboard::Arrow && arrowInput == Keyboard::ArrowLeft) || ((char)input == 'A' || (char)input == 'a'))
        {
            --x;
            m_symbol = kGoingLeftSymbol;
        }

        GameObject* gameObject = m_pLevel->GameObjectGet(x, y);
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