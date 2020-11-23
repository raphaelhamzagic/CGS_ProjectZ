#pragma once
#include "PlaceableActor.h"

namespace projectz
{
    namespace game
    {
        class GameplayState;
        struct SpittingCreatureProjectile;

        class SpittingCreature : public PlaceableActor
        {
        public:
            enum class State
            {
                STATE_AIMING, 
                STATE_STOPPED, // player is not at sight
                STATE_SHOOTING, // player is in the same coordinate (y axis)
                STATE_RECOVERING // hit by player
            };

            SpittingCreature(int x, int y, char symbol, char projectileSymbol, int shootingDirectionX);
            ~SpittingCreature();
            virtual ActorType GetType() override;
            virtual void Draw(const HANDLE& console);
            bool Update(const int playerX, const int playerY, GameplayState* pOwner);
            virtual void TakeDamage() override;

        private:
            char m_projectileSymbol;
            std::vector<SpittingCreatureProjectile*> m_projectiles;

            State m_state;
            int m_shootingInterval;
            int m_recoveringInterval;
            int m_shootingDirectionX;

            int GetDirection(const int value);
            bool Shoot(const int playerX, const int playerY);
            bool UpdateProjectiles(const int playerX, const int playerY, GameplayState* pOwner);
            bool UpdateCreature(const int playerX, const int playerY, GameplayState* pOwner);
        };
    }
}
