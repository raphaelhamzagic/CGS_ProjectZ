#include "Goal.h"
#include <iostream>

Goal::Goal(int x, int y)
    : PlaceableActor(x, y)
{
}

void Goal::Draw()
{
    std::cout << "X";
}
