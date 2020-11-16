#include "PlaceableActor.h"
#include "Point.h"

namespace projectz {
    namespace game {

        PlaceableActor::PlaceableActor(int x, int y, ActorColor color)
            : m_pPosition(new Point(x, y))
            , m_pDirection(new Point())
            , m_IsActive(true)
            , m_color(color)
        {
        }

        PlaceableActor::~PlaceableActor()
        {
            delete m_pPosition;
            m_pPosition = nullptr;
        }

        int PlaceableActor::GetXPosition()
        {
            return m_pPosition->x;
        }

        int PlaceableActor::GetYPosition()
        {
            return m_pPosition->y;
        }

        int* PlaceableActor::GetXPositionPointer()
        {
            return &(m_pPosition->x);
        }

        int* PlaceableActor::GetYPositionPointer()
        {
            return &(m_pPosition->y);
        }

        void PlaceableActor::SetPosition(int x, int y)
        {
            if (x != m_pPosition->x)
            {
                if (x > m_pPosition->x)
                {
                    m_pDirection->x = 1;
                }
                else
                {
                    m_pDirection->x = -1;
                }
                m_pPosition->x = x;
            }
            else
            {
                m_pDirection->x = 0;
            }

            if (y != m_pPosition->y)
            {
                if (y > m_pPosition->y)
                {
                    m_pDirection->y = 1;
                }
                else
                {
                    m_pDirection->y = -1;
                }
                m_pPosition->y = y;
            }
            else
            {
                m_pDirection->y = 0;
            }           
        }

        Point PlaceableActor::GetDirection()
        {
            return *m_pDirection;
        }

        Point PlaceableActor::GetPosition()
        {
            return *m_pPosition;
            return *m_pPosition;
        }

        Point* PlaceableActor::GetPositionPointer()
        {
            return m_pPosition;
        }

        void PlaceableActor::Place(int x, int y)
        {
            m_pPosition->x = x;
            m_pPosition->y = y;
            m_IsActive = true;
        }

    }
}