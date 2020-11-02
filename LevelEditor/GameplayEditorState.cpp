#include <iostream>
#include <conio.h>

#include "GameplayEditorState.h"
#include "BlueprintEditorState.h"
#include "LevelEditorStateMachine.h"
#include "Level.h"
#include "Point.h"

using namespace std;

namespace projectz {
    namespace editor {

        GameplayEditorState::GameplayEditorState(LevelEditorStateMachine* stateMachine)
            : EditorState(stateMachine)
            , m_pCursor(nullptr)
        {
        }

        void GameplayEditorState::Enter()
        {
            m_pCursor = new Point();
        }

        void GameplayEditorState::Exit()
        {
            if (m_pCursor)
            {
                delete m_pCursor;
                m_pCursor = nullptr;
            }
        }

        bool GameplayEditorState::Update()
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
                    m_pStateMachine->m_pLevel->SaveLevel();
                    return false;
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

                    if (!IsWall(pLevelBlueprint[index]))
                    {
                        if 
                        (
                            (IsDoor(pLevelBlueprint[index]) && IsDoor(inputChar))
                            ||
                            (IsWindow(pLevelBlueprint[index]) && IsWindow(inputChar))
                            ||
                            IsValidChar(inputChar)
                        )
                        {
                            pLevelGameplay[index] = inputChar;
                        }
                    }
                }
            }

            return true;
        }


        void GameplayEditorState::UpdateCursor()
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


        void GameplayEditorState::Draw()
        {
            system("cls");

            DrawCanvasTopBorder();
            DrawEditorTitle();
            DrawCanvasEmptyLine();
            DrawCanvasEmptyLine();

            char* pLevelGameplay = m_pStateMachine->m_pLevel->GetLevelGameplay();
            for (int y = 0; y < m_pStateMachine->m_pLevel->GetLevelHeight(); ++y)
            {
                DrawCanvasLeftBorder();
                for (int x = 0; x < m_pStateMachine->m_pLevel->GetLevelWidth(); ++x)
                {
                    if (m_pCursor->x == x && m_pCursor->y == y)
                    {
                        cout << kCursor;
                    }
                    else
                    {
                        int index = m_pStateMachine->m_pLevel->GetIndexFromXY(x, y);
                        cout << pLevelGameplay[index];
                    }
                }
                DrawCanvasRightBorder();
            }

            DrawCanvasEmptyLine();
            DrawCanvasEmptyLine();
            DrawCanvasBottomBorder();

            // DrawLegend();
        }

        void GameplayEditorState::DrawCanvasTopBorder()
        {
            cout << kTopLeftBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << kHorizontalBorder;
            }
            cout << kTopRightBorder << endl;
        }

        void GameplayEditorState::DrawCanvasMiddleBorder()
        {
            cout << kMiddleLeftBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << kHorizontalBorder;
            }
            cout << kMiddleRightBorder << endl;
        }

        void GameplayEditorState::DrawCanvasLeftBorder()
        {
            cout << kVerticalBorder;
            DrawCanvasHorizontalMargin();
        }

        void GameplayEditorState::DrawCanvasRightBorder()
        {
            DrawCanvasHorizontalMargin();
            cout << kVerticalBorder << endl;
        }

        void GameplayEditorState::DrawCanvasHorizontalMargin()
        {
            int marginH = (kCanvasWidth - kLevelWidth) / 2;
            for (int i = 0; i < marginH; i++)
            {
                cout << " ";
            }
        }

        void GameplayEditorState::DrawCanvasEmptyLine()
        {
            cout << kVerticalBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << " ";
            }
            cout << kVerticalBorder << endl;
        }

        void GameplayEditorState::DrawCanvasBottomBorder()
        {
            cout << kBottomLeftBorder;
            for (int i = 0; i < kCanvasWidth; i++)
            {
                cout << kHorizontalBorder;
            }
            cout << kBottomRightBorder << endl;
        }

        void GameplayEditorState::DrawEditorTitle()
        {
            cout << kVerticalBorder;
            string title = "Editing level gameplay (" + m_pStateMachine->m_pLevel->GetLevelFilename() + ")";
            cout << title;
            int margin = kCanvasWidth - title.size();
            for (int i = 0; i < margin; i++)
            {
                cout << " ";
            }
            cout << kVerticalBorder << endl;
        }

        void GameplayEditorState::DrawLegend()
        {
            cout << "Navigation" << endl;
            cout << "----------" << endl;
            cout << "Arrow keys: Move cursor" << endl;
            cout << "ESC key: Save and finish editing" << endl << endl;

            cout << "Characters" << endl;
            cout << "----------" << endl;
            cout << kPlayerStart << ": player start" << endl;
            cout << kZombie << ": zombies" << endl;
            cout << kLeftShootingCreature << kRightShootingCreature << ": left and right shooting creatures" << endl << endl;
            
            cout << "Doors" << endl;
            cout << "--------------" << endl;
            cout << "horizontal brown: " << kHorizontalBrownDoor << endl;
            cout << "vertical brown: " << kVerticalBrownDoor << endl;
            cout << "blue (horizontal): " << kHorizontalBlueDoor << endl;
            cout << "blue (vertical): " << kVerticalBlueDoor << endl;
            cout << "cyan (horizontal): " << kHorizontalCyanDoor << endl;
            cout << "cyan (vertical): " << kVerticalCyanDoor << endl;
            cout << "green (horizontal): " << kHorizontalGreenDoor << endl;
            cout << "green (vertical): " << kVerticalGreenDoor << endl;
            cout << "magenta (horizontal): " << kHorizontalMagentaDoor << endl;
            cout << "magenta (vertical): " << kVerticalMagentaDoor << endl;
            cout << "red (horizontal): " << kHorizontalRedDoor << endl;
            cout << "red (vertical): " << kVerticalRedDoor << endl;
            cout << "yellow (horizontal): " << kHorizontalYellowDoor << endl;
            cout << "yellow (vertical): " << kVerticalYellowDoor << endl << endl;

            cout << "Items" << endl;
            cout << "-----" << endl;
            cout << kLife << ": life" << endl;
            cout << kWood << ": wood" << endl;
            cout << kSerum << ": serum" << endl << endl;

            cout << "Keys" << endl;
            cout << "--------------" << endl;
            cout << "brown: " << kBrownKey << endl;
            cout << "blue: " << kBlueKey << endl;
            cout << "cyan: " << kCyanKey << endl;
            cout << "green: " << kGreenKey << endl;
            cout << "magenta: " << kMagentaKey << endl;            
            cout << "red: " << kRedKey << endl;
            cout << "yellow: " << kYellowKey << endl << endl;

            cout << "Weapons" << endl;
            cout << "-------" << endl;
            cout << kGun << ": gun" << endl;
            cout << kGunAmmo << ": gun ammo" << endl;
            cout << kShotgun << ": shotgun" << endl;
            cout << kShotgunAmmo << ": shotgun ammo" << endl << endl;
        }

        void GameplayEditorState::Save()
        {
            m_pStateMachine->m_pLevel->SaveLevel();
        }

        bool GameplayEditorState::IsDoor(char input)
        {
            switch (input)
            {
                case kDoor: //case kHorizontalGreenDoor:
                case kHorizontalBrownDoor:
                case kVerticalBrownDoor:
                case kHorizontalBlueDoor:
                case kVerticalBlueDoor:
                case kHorizontalCyanDoor:
                case kVerticalCyanDoor:                
                case kVerticalGreenDoor:
                case kHorizontalMagentaDoor:
                case kVerticalMagentaDoor:
                case kHorizontalRedDoor:
                case kVerticalRedDoor:
                case kHorizontalYellowDoor:
                case kVerticalYellowDoor:
                    return true;
            }
            return false;
        }

        

        bool GameplayEditorState::IsWindow(char input)
        {
            switch (input)
            {
                kWindow:
                kVerticalWindow:
                kHorizontalWindow:
                    return true;
            }
            return false;
        }

        bool GameplayEditorState::IsWall(char input)
        {
            switch (input)
            {
                kWall1:
                kWall2:
                kWall3:
                    true;
            }
            return false;
        }

        bool GameplayEditorState::IsValidChar(char input)
        {
            switch (input)
            {
                case kGun:
                case kGunAmmo:
                case kShotgun:
                case kShotgunAmmo:

                case kLife:
                case kWood:
                case kSerum:

                case kBrownKey:
                case kBlueKey:
                case kCyanKey:
                case kGreenKey:
                case kMagentaKey:
                case kRedKey:
                case kYellowKey:

                case kHorizontalWindow:
                case kVerticalWindow:

                case kZombie:
                case kLeftShootingCreature:
                case kRightShootingCreature:
                case kPlayerStart:
                case kCabinet:
                case kEmpty:
                    return true;
            }
            return false;
        }

    }
}