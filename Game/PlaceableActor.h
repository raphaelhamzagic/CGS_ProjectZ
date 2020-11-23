#pragma once
#include <Windows.h>

namespace projectz 
{
    namespace game 
    {
        enum class ActorColor
        {
            Blue = 1,
            Green = 2,
            Cyan = 3,
            Red = 4,
            Magenta = 5,
            Brown = 6,
            LightGray = 7,
            DarkGray = 8,
            LightBlue = 9,
            LightGreen = 10,
            LightCyan = 11,
            LightRed = 12,
            LightMagenta = 13,
            Yellow = 14,
            White = 15,
            SolidGreen = 34,
            SolidRed = 68,
            SolidBlue = 153
        };

        enum class ActorType
        {
            Door,
            Enemy,
            Goal,
            Key,
            Money,
            Player,
            Zombie,
            Gun,
            GunAmmo,
            HealthKit,
            SpittingCreature
        };

        class Point;

        class PlaceableActor
        {
        public:
            PlaceableActor(int x, int y, char symbol, ActorColor color = ActorColor::LightGray);
            virtual ~PlaceableActor();

            int GetXPosition();
            int GetYPosition();
            int GetXDirection();
            int GetYDirection();
            void SetPosition(int x, int y);
            void SetDirection(int x, int y);
            int GetLastXPosition();
            int GetLastYPosition();

            ActorColor GetColor() { return m_color; }

            void Place(int x, int y);
            void Remove();
            bool IsActive() { return m_isActive; }

            virtual ActorType GetType() = 0;
            virtual void Draw(const HANDLE& console);
            virtual void Update();
            virtual void TakeDamage();

        protected:
            Point* m_pPosition;
            Point* m_pLastPosition;
            Point* m_pDirection;
            bool m_isActive;
            char m_symbol;
            ActorColor m_color;
        };
    }
}