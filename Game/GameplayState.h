#pragma once
#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include <Windows.h>
#include <vector>
#include <string>


namespace projectz {
    namespace game {
        class StateMachineExampleGame;

        class GameplayState : public GameState
        {
            StateMachineExampleGame* m_pOwner;

            Player m_player;
            Level* m_pLevel;

            bool m_levelLoaded;
            bool m_beatLevel;
            int m_skipFrameCount;
            static constexpr int kFramesToSkip = 2;

            int m_currentLevel;
            std::vector<std::string> m_LevelNames;


        public:
            GameplayState(StateMachineExampleGame* pOwner);
            ~GameplayState();
            virtual void Enter() override;
            virtual bool Update(bool processInput = true) override;
            virtual void Draw() override;

        private:
            void Load();
            void HandleCollision(int newPlayerX, int newPlayerY);
            void DrawHUD(const HANDLE& console);
        };
    }
}