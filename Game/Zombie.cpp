#include "Zombie.h"
#include <iostream>

namespace projectz {
    namespace game {
        Zombie::Zombie(int x, int y)
            : PlaceableActor(x, y)
        {

        }

        void Zombie::Draw()
        {
            std::cout << 'z';
        }

        void Zombie::Update(int* playerX, int* playerY)
        {
            int diffX = *playerX - m_pPosition->x;
            int diffY = *playerY - m_pPosition->y;
            int directionX = 0;
            if (diffX > 0)
            {
                directionX = 1;
            }
            else if (diffX < 0)
            {
                directionX = -1;
            }

            int directionY = 0;
            if (diffY > 0)
            {
                directionY = 1;
            }
            else if (diffY < 0)
            {
                directionY = -1;
            }

            int newPositionX = m_pPosition->x + directionX;
            int newPositionY = m_pPosition->y + directionY;
            SetPosition(newPositionX, newPositionY);
        }

    }
}
