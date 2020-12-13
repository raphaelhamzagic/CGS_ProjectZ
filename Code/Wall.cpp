#include <iostream>
#include "Wall.h"



Wall::Wall(int x, int y)
    : GameObject{x, y}
{
}

void Wall::Draw()
{
    std::cout << (char)219;
}
