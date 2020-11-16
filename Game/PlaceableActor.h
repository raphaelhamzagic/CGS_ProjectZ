#pragma once

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
            HealthKit
        };

        enum class ActorOrientation
        {
            Horizontal,
            Vertical
        };

        class Point;
        class Level; // TODO try to remove

        class PlaceableActor
        {
        public:
            PlaceableActor(int x, int y, ActorColor color = ActorColor::LightGray);
            virtual ~PlaceableActor();

            int GetXPosition();
            int GetYPosition();
            int* GetXPositionPointer();
            int* GetYPositionPointer();
            Point GetPosition();
            Point* GetPositionPointer();
            void SetPosition(int x, int y);

            Point GetDirection();

            ActorColor GetColor() { return m_color; }

            void Remove() { m_IsActive = false; }
            bool IsActive() { return m_IsActive; }
            void Place(int x, int y);

            virtual ActorType GetType() = 0;
            virtual void Draw() = 0;
            virtual bool Update() { return false; };
            virtual bool Update(Level* pLevel, int playerX, int playerY) { return false; };

            virtual void TakeDamage(const Point* pDamageDirection = nullptr) {};

        protected:
            Point* m_pPosition;

            bool m_IsActive;
            ActorColor m_color;

            Point* m_pDirection;
        };
    }
}