#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Key;

        class Player : public PlaceableActor
        {
        public:
            Player();

            virtual ActorType GetType() override { return ActorType::Player; }
            virtual void Draw() override;

            bool HasKey();
            bool HasKey(ActorColor color);
            void PickupKey(Key* key);
            void UseKey();
            void DropKey();
            Key* GetKey() { return m_pCurrentKey; }

            int GetLives() { return m_lives; }
            void TakeDamage();
            bool IsAlive();

        private:
            Key* m_pCurrentKey;
            int m_lives;
        };
    }
}