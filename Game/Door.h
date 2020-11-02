#pragma once
#include "PlaceableActor.h"
namespace projectz {
    namespace game {
        class Door : public PlaceableActor
        {
        public:
            Door(int x, int y, ActorOrientation orientation, ActorColor color, ActorColor closedColor);
            virtual void Draw() override;

            virtual ActorType GetType() override { return ActorType::Door; }
            ActorOrientation GetOrientation() { return m_orientation; }
            bool IsOpen() { return m_isOpen; }
            void Open() { m_isOpen = true; }

        private:
            bool m_isOpen;
            ActorOrientation m_orientation;
            ActorColor m_closedColor;
        };
    }
}