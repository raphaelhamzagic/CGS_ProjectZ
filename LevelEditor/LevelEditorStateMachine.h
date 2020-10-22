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
        LevelEditor
    };
    Level* m_pLevel;

private:
    EditorState* m_pCurrentState;

public:
    LevelEditorStateMachine();

    void Initialize();
    bool UpdateCurrentState();
    void DrawCurrentState();
    void ChangeState(StateName newState);
    void Deinitialize();

private:
    EditorState* LoadState(StateName stateName);
};

