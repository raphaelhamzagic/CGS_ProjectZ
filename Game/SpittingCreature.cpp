#include <algorithm>
#include <vector>
#include "SpittingCreature.h"
#include "Point.h"

namespace projectz
{
    namespace game
    {
        SpittingCreature::SpittingCreature (int x, int y, char symbol)
            : PlaceableActor(x, y, symbol)
        {
        }

        ActorType SpittingCreature::GetType()
        {
            return ActorType::SpittingCreature;
        }

        bool SpittingCreature::Update(const int playerX, const int playerY, const std::vector<Point>& emptyPositionsAround)
        {
            bool hasHitPlayer = false;
            if (m_isActive)
            {
                int diffY = playerY - m_pPosition->y;
                int directionY = GetDirection(diffY);
                if (directionY == 0)
                {
                    Shoot(playerX);
                }
                else
                {
                    int newPositionY = m_pPosition->y + directionY;
                    Point newPosition{ m_pPosition->x, newPositionY };
                    auto found = std::find(emptyPositionsAround.begin(), emptyPositionsAround.end(), newPosition);
                    if (found != emptyPositionsAround.end())
                    {
                        SetPosition(newPosition.x, newPosition.y);
                    }
                }
                
            }            
            return hasHitPlayer;
        }

        int SpittingCreature::GetDirection(const int value)
        {
            int direction{};
            if (value > 0)
            {
                direction = 1;
            }
            else if (value < 0)
            {
                direction = -1;
            }
            return direction;
        }

        void SpittingCreature::Shoot(const int playerX)
        {

        }

        
    }
}