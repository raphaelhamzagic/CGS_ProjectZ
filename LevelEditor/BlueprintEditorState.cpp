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
            m_pStateMachine->m_pLevel->SetBlueprintCharacter(m_pCursor, static_cast<char>(input));
        }
    }

    return true;
}


void BlueprintEditorState::UpdateCursor()
{
    Point* pNewCursor = new Point();
    int arrowInput = _getch();
    switch (arrowInput)
    {
        case kLeftArrow:
            pNewCursor->x--;
            break;
        case kRightArrow:
            pNewCursor->x++;
            break;
        case kUpArrow:
            pNewCursor->y--;
            break;
        case kDownArrow:
            pNewCursor->y++;
            break;
    }

    if (pNewCursor->x < 0)
    {
        pNewCursor->x = 0;
    }
    else if (pNewCursor->x == m_pStateMachine->m_pLevel->GetWidth())
    {
        pNewCursor->x = m_pStateMachine->m_pLevel->GetWidth() - 1;
    }

    if (pNewCursor->y < 0)
    {
        pNewCursor->y = 0;
    }
    else if (pNewCursor->y == m_pStateMachine->m_pLevel->GetHeight())
    {
        pNewCursor->y = m_pStateMachine->m_pLevel->GetHeight() - 1;
    }

    delete m_pCursor;
    m_pCursor = pNewCursor;
}

void BlueprintEditorState::Draw()
{
    system("cls");
    m_pStateMachine->m_pLevel->DrawBlueprint(m_pCursor);
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
    m_pStateMachine->m_pLevel->Save();
}

void BlueprintEditorState::Exit()
{
    if (m_pCursor)
    {
        delete m_pCursor;
        m_pCursor = nullptr;
    }
}
