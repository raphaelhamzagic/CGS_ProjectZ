#pragma once

class LevelEditorStateMachine;

class LevelEditor
{
    LevelEditorStateMachine* m_pStateMachine;

public:
    LevelEditor();
    void Initialize();
    void RunGameLoop();
    void Deinitialize();
};

