#include "Point.h"

namespace projectz 
{
    namespace game 
    {
        Point::Point()
            : x(0)
            , y(0)
        {
        }

        Point::Point(int x, int y)
            : x(x)
            , y(y)
        {
        }

        double Point::DistanceTo(int x, int y)
        {
            x = x - this->x;
            y = y - this->y;
            x *= x;
            y *= y;
            return sqrt(
                x + y
            );
        }

        Point operator+(const Point &p1, const Point &p2) 
        {
            return Point(p1.x + p2.x, p1.y + p2.y);
        }

        bool operator==(const Point& p1, const Point& p2)
        {
            return p1.x == p2.x && p1.y == p2.y;
        }


    }
}