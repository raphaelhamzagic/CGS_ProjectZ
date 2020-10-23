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

void MainMenuState::Draw()
{
    system("cls");
    cout << "Please select one of the following options:" << endl;
    cout << kOptionLoadLevel << ". Load Level" << endl;
    cout << kOptionNewLevel << ". New Level" << endl;
    cout << kOptionQuit << ". Quit" << endl;
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
