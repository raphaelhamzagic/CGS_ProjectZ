#include <iostream>
#include "MainMenuState.h"
#include "LevelEditorStateMachine.h"
#include "Level.h"

using namespace std;

MainMenuState::MainMenuState(LevelEditorStateMachine* stateMachine)
    : EditorState(stateMachine)
{
}

void MainMenuState::Enter()
{
}


bool MainMenuState::Update()
{
    Draw();
    bool updateResult{ true };

    int input;
    cin >> input;

    switch (input)
    {
        case kOptionLoadLevel:
            LoadLevel();
            break;

        case kOptionNewLevel:
            NewLevel();
            break;

        case kOptionQuit:
            updateResult = false;
            break;

        default:
            // invalid option
            break;
    }

    return updateResult;
}

void MainMenuState::Exit()
{
}

void MainMenuState::LoadLevel()
{
    Level* pLevel = new Level();
    if (pLevel->LoadLevel())
    {
        m_pStateMachine->m_pLevel = pLevel;
        m_pStateMachine->ChangeState(LevelEditorStateMachine::StateName::BlueprintEditor);
    }
}

void MainMenuState::NewLevel()
{
    Level* pLevel = new Level();
    pLevel->NewLevel();
    m_pStateMachine->m_pLevel = pLevel;
    m_pStateMachine->ChangeState(LevelEditorStateMachine::StateName::BlueprintEditor);
}

void MainMenuState::Draw()
{
    system("cls");

    DrawCanvasTopBorder();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();

    DrawCanvasLeftBorder();
    cout << "                                 Please select one of the following options:                                  ";
    DrawCanvasRightBorder();

    DrawCanvasEmptyLine();

    DrawCanvasLeftBorder();
    cout << "                                 " << kOptionLoadLevel << ". Load Level                                                                ";
    DrawCanvasRightBorder();

    DrawCanvasLeftBorder();
    cout << "                                 " << kOptionNewLevel << ". New Level                                                                 ";
    DrawCanvasRightBorder();

    DrawCanvasLeftBorder();
    cout << "                                 " << kOptionQuit << ". Quit                                                                      ";
    DrawCanvasRightBorder();

    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    DrawCanvasEmptyLine();
    
    DrawCanvasBottomBorder();
}

void MainMenuState::DrawCanvasTopBorder()
{
    cout << kTopLeftBorder;
    for (int i = 0; i < kCanvasWidth; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}

void MainMenuState::DrawCanvasLeftBorder()
{
    cout << kVerticalBorder;
}

void MainMenuState::DrawCanvasRightBorder()
{
    cout << kVerticalBorder << endl;
}

void MainMenuState::DrawCanvasEmptyLine()
{
    cout << kVerticalBorder;
    for (int i = 0; i < kCanvasWidth; i++)
    {
        cout << " ";
    }
    cout << kVerticalBorder << endl;
}

void MainMenuState::DrawCanvasBottomBorder()
{
    cout << kBottomLeftBorder;
    for (int i = 0; i < kCanvasWidth; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;
}