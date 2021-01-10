#pragma once
#include "GameObject.h"

class Level;
class Wall : public GameObject
{
    static char constexpr kMainSymbol = (char)219;

public:
    Wall(int x, int y, Level* pLevel);
};
