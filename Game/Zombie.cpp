#include "Zombie.h"
#include <iostream>
#include <Windows.h>

using namespace std;

namespace projectz {
    namespace game {
        int Zombie::s_count = 0;

        Zombie::Zombie(int x, int y)
            : PlaceableActor(x, y)
            , m_color(ActorColor::Red)
        {
            m_id = s_count++;
        }

        void Zombie::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)m_color);
            std::cout << 'z';
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }

        void Zombie::Update(int playerX, int playerY)
        {
            int newPositionX = m_pPosition->x;
            int newPositionY = m_pPosition->y;

            int diffX = playerX - m_pPosition->x;
            int diffY = playerY - m_pPosition->y;
            
            int directionX = 0;
            int directionY = 0;

            if (diffX > 0)
            {
                directionX = 1;
            }
            else if (diffX < 0)
            {
                directionX = -1;
            }
            newPositionX = m_pPosition->x + directionX;

            if (diffY > 0)
            {
                directionY = 1;
            }
            else if (diffY < 0)
            {
                directionY = -1;
            }
            newPositionY = m_pPosition->y + directionY;

            if (newPositionX != m_pPosition->x && newPositionY != m_pPosition->y)
            {
                int randomAxis = rand() % 2;
                if (randomAxis)
                {
                    SetPosition(newPositionX, m_pPosition->y);
                }
                else
                {
                    SetPosition(m_pPosition->x, newPositionY);
                }
            }
            else if (newPositionX != m_pPosition->x)
            {
                SetPosition(newPositionX, m_pPosition->y);
            }
            else if (newPositionY != m_pPosition->y)
            {
                SetPosition(m_pPosition->x, newPositionY);
            }
            else
            {
                SetPosition(m_pPosition->x, m_pPosition->y);
            }
        }
    }
}
