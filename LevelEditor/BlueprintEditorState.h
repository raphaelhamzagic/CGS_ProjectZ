#pragma once
#include "EditorState.h"

class Point;

class BlueprintEditorState : public EditorState
{
    static constexpr int kArrowInput = 224;
    static constexpr int kLeftArrow = 75;
    static constexpr int kRightArrow = 77;
    static constexpr int kUpArrow = 72;
    static constexpr int kDownArrow = 80;

    static constexpr int kEscape = 27;
    static constexpr int kBackspace = 8;

    Point* m_pCursor;
public:
    BlueprintEditorState(LevelEditorStateMachine* stateMachine);
    virtual ~BlueprintEditorState() = default;

    virtual void Enter() override;
    virtual bool Update() override;
    virtual void Draw() override;
    virtual void Exit() override;

private:
    void UpdateCursor();
    void DrawLegend();
    void Save();
};
