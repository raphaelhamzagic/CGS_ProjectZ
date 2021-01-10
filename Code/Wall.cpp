#include "Wall.h"
#include "Level.h"

Wall::Wall(int x, int y, Level* pLevel)
    : GameObject{x, y, Wall::kMainSymbol, GameObjectType::WALL, pLevel}
{
}
