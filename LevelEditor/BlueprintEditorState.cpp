#include <iostream>
#include <conio.h>

#include "BlueprintEditorState.h"
#include "LevelEditorStateMachine.h"
#include "Level.h"
#include "Point.h"

using namespace std;

namespace projectz {
    namespace editor {

        BlueprintEditorState::BlueprintEditorState(LevelEditorStateMachine* stateMachine)
            : EditorState(stateMachine)
            , m_pCursor(nullptr)
        {
        }

        void BlueprintEditorState::Enter()
        {
            m_pCursor = new Point();
        }

        void BlueprintEditorState::Exit()
        {
            if (m_pCursor)
            {
                delete m_pCursor;
                m_pCursor = nullptr;
            }
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
                    // done editing the level blueprint, switch to level gameplay editing
                    m_pStateMachine->m_pLevel->SaveLevel();
                    m_pStateMachine->ChangeState(LevelEditorStateMachine::StateName::GameplayEditor);
                }
                else if (input == kBackspace)
                {
                    // ignore input
                }
                else
                {
                    char inputChar = static_cast<char>(input);
                    char* pLevelBlueprint = m_pStateMachine->m_pLevel->GetLevelBlueprint();
                    char* pLevelGameplay = m_pStateMachine->m_pLevel->GetLevelGameplay();
                    int index = m_pStateMachine->m_pLevel->GetIndexFromXY(m_pCursor->x, m_pCursor->y);
                    if (IsWall(inputChar) || IsDoor(inputChar) || IsWindow(inputChar) || IsEmpty(inputChar))
                    {
                        pLevelBlueprint[index] = inputChar;
                        pLevelGameplay[index] = inputChar;
                    }
                    else if (IsRoom(inputChar))
                    {
                        pLevelBlueprint[index] = inputChar;
                    }
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
            else if (newCursor.x == m_pStateMachine->m_pLevel->GetLevelWidth())
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

        void BlueprintEditorState::DrawCanvasTopBorder()
        {
            cout << kTopLeftBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << kHorizontalBorder;
            }
            cout << kTopRightBorder << endl;
        }

        void BlueprintEditorState::DrawCanvasLeftBorder()
        {
            cout << kVerticalBorder;
            DrawCanvasHorizontalMargin();
        }

        void BlueprintEditorState::DrawCanvasRightBorder()
        {
            DrawCanvasHorizontalMargin();
            cout << kVerticalBorder << endl;
        }

        void BlueprintEditorState::DrawCanvasHorizontalMargin()
        {
            int marginH = (kCanvasWidth - kLevelWidth) / 2;
            for (int i = 0; i < marginH; i++)
            {
                cout << " ";
            }
        }

        void BlueprintEditorState::DrawCanvasVerticalMargin()
        {
            DrawCanvasEmptyLine();
            DrawCanvasEmptyLine();
        }

        void BlueprintEditorState::DrawCanvasEmptyLine()
        {
            cout << kVerticalBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << " ";
            }
            cout << kVerticalBorder << endl;
        }

        void BlueprintEditorState::DrawCanvasBottomBorder()
        {
            cout << kBottomLeftBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << kHorizontalBorder;
            }
            cout << kBottomRightBorder << endl;
        }

        void BlueprintEditorState::Draw()
        {
            system("cls");

            DrawCanvasTopBorder();
            DrawEditorTitle();
            DrawCanvasEmptyLine();
            DrawCanvasEmptyLine();

            char* pBlueprint = m_pStateMachine->m_pLevel->GetLevelBlueprint();
            for (int y = 0; y < m_pStateMachine->m_pLevel->GetLevelHeight(); y++)
            {
                DrawCanvasLeftBorder();
                for (int x = 0; x < m_pStateMachine->m_pLevel->GetLevelWidth(); x++)
                {
                    if (m_pCursor->x == x && m_pCursor->y == y)
                    {
                        cout << kCursor;
                    }
                    else
                    {
                        int index = m_pStateMachine->m_pLevel->GetIndexFromXY(x, y);
                        cout << pBlueprint[index];
                    }
                }
                DrawCanvasRightBorder();
            }

            DrawCanvasEmptyLine();
            DrawCanvasEmptyLine();
            DrawCanvasBottomBorder();

            DrawLegend();
        }

        void BlueprintEditorState::DrawEditorTitle()
        {
            cout << kVerticalBorder;
            string title = "Editing level blueprint (" + m_pStateMachine->m_pLevel->GetLevelFilename() + ")";
            cout << title;
            int margin = kCanvasWidth - title.size();
            for (int i = 0; i < margin; i++)
            {
                cout << " ";
            }
            cout << kVerticalBorder << endl;
        }

        void BlueprintEditorState::DrawLegend()
        {
            cout << "Navigation" << endl;
            cout << "----------" << endl;
            cout << "Arrow keys: Move cursor" << endl;
            cout << "ESC key: Save and finish editing" << endl << endl;

            cout << kWall1 << kWall2 << kWall3 << ": walls" << endl;
            cout << kDoor << ": doors" << endl;
            cout << kWindow << ": windows" << endl;
            cout << kRoomA << kRoomB << kRoomC << kRoomD << kRoomE << kRoomF << kRoomG << kRoomH << kRoomI << kRoomJ << kRoomK << kRoomL << kRoomM << kRoomN << ": rooms" << endl;
        }

        void BlueprintEditorState::Save()
        {
            m_pStateMachine->m_pLevel->SaveLevel();
        }

        bool BlueprintEditorState::IsWall(char input)
        {
            switch (input)
            {
            case kWall1:
            case kWall2:
            case kWall3:
                return true;
            }
            return false;
        }

        bool BlueprintEditorState::IsDoor(char input)
        {
            return input == kDoor;
        }

        bool BlueprintEditorState::IsWindow(char input)
        {
            return input == kWindow;
        }

        bool BlueprintEditorState::IsEmpty(char input)
        {
            return input == kEmpty;
        }

        bool BlueprintEditorState::IsRoom(char input)
        {
            switch (input)
            {
            case kRoomA:
            case kRoomB:
            case kRoomC:
            case kRoomD:
            case kRoomE:
            case kRoomF:
            case kRoomG:
            case kRoomH:
            case kRoomI:
            case kRoomJ:
                return true;
            }
            return false;
        }
    }
}
