#pragma once
#include "PlaceableActor.h"
namespace projectz {
    namespace game {
        class Door : public PlaceableActor
        {
        public:
            Door(int x, int y, ActorOrientation orientation, bool isOpen, ActorColor unlockedColor, ActorColor lockedColor);
            virtual void Draw() override;

            virtual ActorType GetType() override { return ActorType::Door; }
            ActorOrientation GetOrientation() { return m_orientation; }
            bool IsLocked() { return m_isLocked; }
            void Open() { m_isLocked = false; }

        private:
            bool m_isLocked;
            ActorOrientation m_orientation;
            ActorColor m_unlockedColor;
        };
    }
}