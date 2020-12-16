#pragma once
#include "GameObject.h"
#include "Level.h"

class Wall : public GameObject
{
public:
    Wall(int x, int y);
private:
    static char constexpr kMainSymbol = (char)219;
};

