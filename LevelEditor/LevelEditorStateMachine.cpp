#include "LevelEditorStateMachine.h"
#include "EditorState.h"
#include "MainMenuState.h"
#include "BlueprintEditorState.h"
#include "LevelEditorStateMachine.h"

LevelEditorStateMachine::LevelEditorStateMachine()
    : m_pCurrentState(nullptr)
    , m_pLevel(nullptr)
{
}

void LevelEditorStateMachine::Initialize()
{
}

bool LevelEditorStateMachine::UpdateCurrentState()
{
    if (m_pCurrentState)
    {
        return m_pCurrentState->Update();
    }
    return false;
}

void LevelEditorStateMachine::DrawCurrentState()
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Draw();
    }
}

void LevelEditorStateMachine::ChangeState(StateName newState)
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
    }
    m_pCurrentState = LoadState(newState);
    m_pCurrentState->Enter();
}

void LevelEditorStateMachine::Deinitialize()
{
    if (m_pCurrentState)
    {
        m_pCurrentState->Exit();
        delete m_pCurrentState;
        m_pCurrentState = nullptr;
    }

}
 
EditorState* LevelEditorStateMachine::LoadState(StateName stateName)
{
    EditorState* state;
    switch (stateName)
    {
        case StateName::MainMenu:
            state = new MainMenuState(this);
            break;
        case StateName::BlueprintEditor:
            state = new BlueprintEditorState(this);
            break;


    }
}
