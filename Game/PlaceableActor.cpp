#include <iostream>

#include "PlaceableActor.h"
#include "Point.h"

namespace projectz
{
    namespace game
    {
        PlaceableActor::PlaceableActor(int x, int y, char symbol, ActorColor color)
            : m_pPosition(new Point(x, y))
            , m_pLastPosition(new Point(x, y))
            , m_pDirection(new Point())
            , m_symbol(symbol)
            , m_color(color)
            , m_isActive(true)
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

        int PlaceableActor::GetLastXPosition()
        {
            return m_pLastPosition->x;
        }

        int PlaceableActor::GetLastYPosition()
        {
            return m_pLastPosition->y;
        }

        int PlaceableActor::GetXDirection()
        {
            return m_pDirection->x;
        }

        int PlaceableActor::GetYDirection()
        {
            return m_pDirection->y;
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
            }
            else
            {
                m_pDirection->x = 0;
            }
            m_pLastPosition->x = m_pPosition->x;
            m_pPosition->x = x;

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
            }
            else
            {
                m_pDirection->y = 0;
            }
            m_pLastPosition->y = m_pPosition->y;
            m_pPosition->y = y;
        }

        
        void PlaceableActor::SetDirection(int x, int y)
        {
            if (x == 0 || std::abs(x) == 1)
            {
                m_pDirection->x = x;
            }
            if (y == 0 || std::abs(y) == 1)
            {
                m_pDirection->y = y;
            }
        }

        void PlaceableActor::Place(int x, int y)
        {
            SetPosition(x, y);
            m_isActive = true;
        }

        void PlaceableActor::Remove()
        {
            m_isActive = false;
        }

        void PlaceableActor::Update()
        {
        }

        void PlaceableActor::TakeDamage()
        {
        }

        void PlaceableActor::Draw(const HANDLE& console)
        {
            COORD actorCursorPosition;
            actorCursorPosition.X = m_pPosition->x;
            actorCursorPosition.Y = m_pPosition->y;
            SetConsoleCursorPosition(console, actorCursorPosition);

            SetConsoleTextAttribute(console, (int)m_color);
            std::cout << m_symbol;
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
        }
    }
}