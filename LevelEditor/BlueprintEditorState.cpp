#include <iostream>
#include <conio.h>

#include "BlueprintEditorState.h"
#include "LevelEditorStateMachine.h"
#include "Level.h"
#include "Point.h"

using namespace std;

BlueprintEditorState::BlueprintEditorState(LevelEditorStateMachine* stateMachine)
    : EditorState(stateMachine)
    , m_pCursor(nullptr)
{
}

void BlueprintEditorState::Enter()
{
    m_pCursor = new Point();
}

bool BlueprintEditorState::Update()
{  
    // check if any arrow key was pressed
    int input = _getch();
    if (input == kArrowInput)
    {
        UpdateCursor();
    }
    else
    {
        if (input == kEscape)
        {
            // done editing the level
            return false;
        }
        else if (input == kBackspace)
        {
            // ignore input
        }
        else
        {
            m_pStateMachine->m_pLevel->SetLevelBlueprintCharacter(m_pCursor, static_cast<char>(input));
        }
    }

    return true;
}


void BlueprintEditorState::UpdateCursor()
{
    Point newCursor{ m_pCursor->x, m_pCursor->y };
    int arrowInput = _getch();
    switch (arrowInput)
    {
        case kLeftArrow:
            newCursor.x--;
            break;
        case kRightArrow:
            newCursor.x++;
            break;
        case kUpArrow:
            newCursor.y--;
            break;
        case kDownArrow:
            newCursor.y++;
            break;
    }

    if (newCursor.x < 0)
    {
        newCursor.x = 0;
    }
    else if (newCursor .x == m_pStateMachine->m_pLevel->GetLevelWidth())
    {
        newCursor.x = m_pStateMachine->m_pLevel->GetLevelWidth() - 1;
    }

    if (newCursor.y < 0)
    {
        newCursor.y = 0;
    }
    else if (newCursor.y == m_pStateMachine->m_pLevel->GetLevelHeight())
    {
        newCursor.y = m_pStateMachine->m_pLevel->GetLevelHeight() - 1;
    }

    m_pCursor->x = newCursor.x;
    m_pCursor->y = newCursor.y;
}

void BlueprintEditorState::Draw()
{
    system("cls");
    m_pStateMachine->m_pLevel->DrawLevelBlueprint(m_pCursor);
    DrawLegend();
}

void BlueprintEditorState::DrawLegend()
{
    cout << "Arrows to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "r g b for key" << endl;
    cout << "R G B for door" << endl;
    cout << "$ for money" << endl;
    cout << "v for vertical moving enemy" << endl;
    cout << "h for horizontal moving enemy" << endl;
    cout << "e for non-moving enemy" << endl;
    cout << "X for end" << endl;
}

void BlueprintEditorState::Save()
{
    m_pStateMachine->m_pLevel->SaveLevel();
}

void BlueprintEditorState::Exit()
{
    if (m_pCursor)
    {
        delete m_pCursor;
        m_pCursor = nullptr;
    }
}
