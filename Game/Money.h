#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Money : public PlaceableActor
        {
        public:
            Money(int x, int y, int worth);
            virtual ActorType GetType() override { return ActorType::Money; }
            int GetWorth() const { return m_worth; }
            virtual void Draw() override;
        private:
            int m_worth;
        };
    }
}