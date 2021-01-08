#pragma once
#include "GameObject.h"
#include "Level.h"

class Wall : public GameObject
{
    static char constexpr kMainSymbol = (char)219;

public:
    Wall(int x, int y);
};
