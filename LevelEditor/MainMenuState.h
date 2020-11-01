#pragma once
#include "EditorState.h"

namespace projectz {
    namespace editor {
        class MainMenuState : public EditorState
        {
            static constexpr int kOptionLoadLevel = 1;
            static constexpr int kOptionNewLevel = 2;
            static constexpr int kOptionQuit = 3;

        public:
            MainMenuState(LevelEditorStateMachine* stateMachine);
            virtual ~MainMenuState() = default;

            virtual void Enter() override;
            virtual bool Update() override;
            virtual void Draw() override;
            virtual void Exit() override;

        private:
            void LoadLevel();
            void NewLevel();
        };
    }
}