#pragma once
#include "PlaceableActor.h"
namespace projectz
{
    namespace game
    {
        struct DoorConfig
        {
            char symbol;
            bool isLocked;
            ActorColor lockedColor;
            ActorColor unlockedColor;
        };

        class Door : public PlaceableActor
        {
        public:
            Door(int x, int y, char symbol, bool isLocked, ActorColor lockedColor, ActorColor unlockedColor);
            virtual void Draw() override;

            virtual ActorType GetType() override { return ActorType::Door; }
            bool IsLocked() { return m_isLocked; }
            void Open() { m_isLocked = false; }

        private:
            bool m_isLocked;
            ActorColor m_unlockedColor;
        };
    }
}