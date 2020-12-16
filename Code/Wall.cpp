#include "Wall.h"

Wall::Wall(int x, int y)
    : GameObject{x, y, Wall::kMainSymbol, GameObjectType::WALL}
{
}
