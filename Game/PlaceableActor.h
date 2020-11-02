#pragma once
#include "Point.h"

namespace projectz {
    namespace game {
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
            Player
        };

        enum class ActorOrientation
        {
            Horizontal,
            Vertical
        };

        class PlaceableActor
        {
        public:
            PlaceableActor(int x, int y, ActorColor color = ActorColor::LightGray);
            virtual ~PlaceableActor();

            int GetXPosition();
            int GetYPosition();
            int* GetXPositionPointer();
            int* GetYPositionPointer();
            void SetPosition(int x, int y);

            ActorColor GetColor() { return m_color; }

            void Remove() { m_IsActive = false; }
            bool IsActive() { return m_IsActive; }
            void Place(int x, int y);

            virtual ActorType GetType() = 0;
            virtual void Draw() = 0;
            virtual void Update() {};

        protected:
            Point* m_pPosition;

            bool m_IsActive;
            ActorColor m_color;
        };
    }
}