#pragma once
#include <math.h>

namespace projectz 
{
    namespace game 
    {
        class Point
        {
        public:
            int x;
            int y;

            Point();
            Point(int x, int y);
            double DistanceTo(int x, int y);

        };
        Point operator+ (const Point& p1, const Point& p2);
        bool operator== (const Point& p1, const Point& p2);
    }
}