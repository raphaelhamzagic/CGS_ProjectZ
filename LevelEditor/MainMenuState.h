#pragma once
#include "EditorState.h"

class MainMenuState : public EditorState
{
    static constexpr int kOptionLoadLevel = 1;
    static constexpr int kOptionNewLevel = 2;
    static constexpr int kOptionQuit = 3;

    static constexpr int kCanvasWidth = 110;
    static constexpr int kCanvasHeight = 29;

    // border canvas chars
    static constexpr char kTopRightBorder = 187;
    static constexpr char kTopLeftBorder = 201;
    static constexpr char kMiddleRightBorder = 185;
    static constexpr char kMiddleLeftBorder = 204;
    static constexpr char kBottomRightBorder = 188;
    static constexpr char kBottomLeftBorder = 200;
    static constexpr char kHorizontalBorder = 205;
    static constexpr char kVerticalBorder = 186;

public:
    MainMenuState(LevelEditorStateMachine* stateMachine);
    virtual ~MainMenuState() = default;

    virtual void Enter() override;
    virtual bool Update() override;
    virtual void Draw() override;
    virtual void Exit() override;

private:
    void LoadLevel();
    void NewLevel();

    void DrawCanvasTopBorder();
    void DrawCanvasLeftBorder();
    void DrawCanvasRightBorder();
    void DrawCanvasBottomBorder();

    void DrawCanvasVerticalMargin();
    void DrawCanvasEmptyLine();
};

