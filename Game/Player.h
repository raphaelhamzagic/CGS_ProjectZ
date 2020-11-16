#pragma once
#include "PlaceableActor.h"

namespace projectz {
    namespace game {
        class Key;
        class FireWeapon;
        class Ammo;

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
            bool IsAlive();
            virtual void TakeDamage(const Point* pDamageDirection = nullptr) override;

            void PickupGun(FireWeapon* gun);
            bool HasGun();
            int GetAmmo();
            bool ShootFireWeapon();
            void PickupGunAmmo(Ammo* ammo);

            void PickupHealthKit();

        private:
            Key* m_pCurrentKey;

            int m_lives;

            FireWeapon* m_pCurrentFireWeapon;
            bool m_hasGun;
        };
    }
}