#include "EditorState.h"

EditorState::EditorState(LevelEditorStateMachine* stateMachine)
    : m_pStateMachine(stateMachine)
{
}

bool EditorState::Update()
{
    return false;
}
