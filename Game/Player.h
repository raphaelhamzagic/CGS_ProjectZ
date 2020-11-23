#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class Key;
        class FireWeapon;
        class Ammo;
        class Map;

        class Player : public PlaceableActor
        {
        public:
            Player(int x, int y, char aliveRightSymbol, char aliveLefSymbol, char aliveUpSymbol, char aliveDownSymbol, char deadSymbol);

            virtual ActorType GetType() override { return ActorType::Player; }
            virtual void Draw(const HANDLE& console) override;
            
            bool HasKey();
            bool HasKey(ActorColor color);
            void PickupKey(Key* key);
            void UseKey();
            void DropKey();
            Key* GetKey() { return m_pCurrentKey; }

            int GetLives() { return m_lives; }
            bool IsAlive();
            virtual void TakeDamage() override;

            void PickupGun(FireWeapon* gun);
            bool HasGun();
            int GetAmmo();
            bool ShootFireWeapon();
            void PickupGunAmmo(Ammo* ammo);

            void PickupHealthKit();

        private:
            char m_deadSymbol;
            Key* m_pCurrentKey;

            int m_lives;

            FireWeapon* m_pCurrentFireWeapon;
            bool m_hasGun;
        };
    }
}