#pragma once

namespace projectz {
    namespace editor {
        class LevelEditorStateMachine;

        class EditorState
        {
        protected:
            LevelEditorStateMachine* m_pStateMachine;

        public:
            EditorState(LevelEditorStateMachine* stateMachine);
            virtual ~EditorState() = default;

            virtual void Enter() {}
            virtual bool Update();
            virtual void Draw() = 0;
            virtual void Exit() {}
        };
    }
}