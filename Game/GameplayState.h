#pragma once
#include <string>
#include <vector>
#include <Windows.h>

#include "GameState.h"
#include "Map.h"
#include "Player.h"

namespace projectz 
{
    namespace game 
    {
        class StateMachineExampleGame;
        class Zombie;

        class GameplayState : public GameState
        {
            StateMachineExampleGame* m_pOwner;

            Player* m_pPlayer;
            std::vector<PlaceableActor*> m_actors;
            
            Map* m_pMap;
            bool m_isMapLoaded;
            
            int m_currentLevel;
            bool m_beatLevel;
            std::vector<std::string> m_LevelNames;

            bool m_isPlayerHit;
            int m_skipFrameCount;
            static constexpr int kFramesToSkip = 2;

        public:
            GameplayState(StateMachineExampleGame* pOwner);
            ~GameplayState();
            virtual void Enter() override;
            virtual bool Update(bool processInput = true) override;
            virtual void Draw() override;

        private:
            void Load();
            void Unload();
            
            void UpdatePlayer(const int newPlayerX, const int newPlayerY);
            void PlayerShoot();
            void HitEnemy(PlaceableActor* enemy, const int directionX, const int directionY);
            void DrawPlayer(const HANDLE& console);
            void UpdateActors();
            void DrawActors(const HANDLE& console);
            void DrawHUD(const HANDLE& console);

            PlaceableActor* GetActorAtPosition(int x, int y);
            bool IsPositionEmpty(int x, int y);
            void GetEmptyPositionsAround(int x, int y, std::vector<Point>& positions);
        };
    }
}