#pragma once

class EditorState;
class Level;

class LevelEditorStateMachine
{
public:
    enum class StateName
    {
        None,
        MainMenu,
        BlueprintEditor,
        ElementsEditor
    };
    Level* m_pLevel;

private:
    EditorState* m_pCurrentState;

public:
    LevelEditorStateMachine();

    void Initialize(StateName initialState);
    bool UpdateCurrentState();
    void DrawCurrentState();
    void ChangeState(StateName newState);
    void Deinitialize();

private:
    void LoadState(StateName stateName);
};

