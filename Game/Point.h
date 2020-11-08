#pragma once
#include <math.h>

namespace projectz {
    namespace game {
        struct Point
        {
            int x;
            int y;

            Point()
                : x(0)
                , y(0)
            {
            }

            Point(int x, int y)
            {
                this->x = x;
                this->y = y;
            }

            double DistanceTo(int x, int y)
            {
                x = x - this->x;
                y = y - this->y;
                x *= x;
                y *= y;
                return sqrt(
                    x + y
                );
            }
        };
    }
}