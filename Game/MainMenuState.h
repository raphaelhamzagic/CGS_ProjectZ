#pragma once
#include "GameState.h"

namespace projectz {
    namespace game {
        class StateMachineExampleGame;

        class MainMenuState : public GameState
        {
            StateMachineExampleGame* m_pOwner;
        public:
            MainMenuState(StateMachineExampleGame* pOwner);
            ~MainMenuState() = default;

            virtual bool Update(bool processInput = true) override;
            virtual void Draw() override;
        };
    }
}