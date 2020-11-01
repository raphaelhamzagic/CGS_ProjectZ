#include "EditorState.h"

namespace projectz {
    namespace editor {

        EditorState::EditorState(LevelEditorStateMachine* stateMachine)
            : m_pStateMachine(stateMachine)
        {
        }

        bool EditorState::Update()
        {
            return false;
        }
    }
}