#include "Goal.h"
#include <iostream>

namespace projectz {
    namespace game {

        Goal::Goal(int x, int y)
            : PlaceableActor(x, y)
        {
        }

        void Goal::Draw()
        {
            std::cout << "X";
        }
    }
}
