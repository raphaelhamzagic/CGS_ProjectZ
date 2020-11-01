#include "LevelEditorStateMachine.h"
#include "EditorState.h"
#include "MainMenuState.h"
#include "BlueprintEditorState.h"
#include "GameplayEditorState.h"
#include "LevelEditorStateMachine.h"

namespace projectz {
    namespace editor {
        LevelEditorStateMachine::LevelEditorStateMachine()
            : m_pCurrentState(nullptr)
            , m_pLevel(nullptr)
        {
        }

        void LevelEditorStateMachine::Initialize(StateName initialState)
        {
            ChangeState(initialState);
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
            LoadState(newState);
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
            if (m_pLevel)
            {
                delete m_pLevel;
                m_pLevel = nullptr;
            }
        }

        void LevelEditorStateMachine::LoadState(StateName stateName)
        {
            switch (stateName)
            {
            case StateName::MainMenu:
                m_pCurrentState = new MainMenuState(this);
                break;
            case StateName::BlueprintEditor:
                m_pCurrentState = new BlueprintEditorState(this);
                break;
            case StateName::GameplayEditor:
                m_pCurrentState = new GameplayEditorState(this);
                break;
            }
        }
    }
}