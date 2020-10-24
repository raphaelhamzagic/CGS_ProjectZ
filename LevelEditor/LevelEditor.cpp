#include "LevelEditor.h"
#include "LevelEditorStateMachine.h"
#include "Level.h"

LevelEditor::LevelEditor()
    : m_pStateMachine(nullptr)
{
}

void LevelEditor::Initialize()
{
    m_pStateMachine = new LevelEditorStateMachine();
    m_pStateMachine->Initialize(LevelEditorStateMachine::StateName::MainMenu);
}

void LevelEditor::RunGameLoop()
{
    if (m_pStateMachine)
    {
        bool isEditing = true;
        while (isEditing)
        {
            isEditing = m_pStateMachine->UpdateCurrentState();
            m_pStateMachine->DrawCurrentState();
        }
        // m_pStateMachine->m_pLevel->SaveLevel();
    }
}

void LevelEditor::Deinitialize()
{
    if (m_pStateMachine)
    {
        m_pStateMachine->Deinitialize();
        delete m_pStateMachine;
        m_pStateMachine = nullptr;
    }
}
