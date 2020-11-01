#include "Money.h"
#include <iostream>

namespace projectz {
    namespace game {

        Money::Money(int x, int y, int worth)
            : PlaceableActor(x, y)
            , m_worth(worth)
        {
        }

        void Money::Draw()
        {
            std::cout << "$";
        }

    }
}