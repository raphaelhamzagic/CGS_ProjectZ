#include <iostream>
#include <conio.h>

#include "GameplayEditorState.h"
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
                    char* pLevelGameplay = m_pStateMachine->m_pLevel->GetLevelGameplay();
                    int index = m_pStateMachine->m_pLevel->GetIndexFromXY(m_pCursor->x, m_pCursor->y);


                    if (!IsWall(pLevelGameplay[index]))
                    {
                        // make sure we update doors with doors types
                        if (IsDoor(inputChar))
                        {
                            if (IsDoor(pLevelGameplay[index]))
                            {
                                pLevelGameplay[index] = inputChar;
                            }
                        }
                        else if (IsValidChar(inputChar))
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

            DrawLegend();
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

            cout << "Weapons" << endl;
            cout << "-------" << endl;
            cout << kGun << ": gun" << endl;
            cout << kGunAmmo << ": gun ammo" << endl;
            cout << kShotgun << ": shotgun" << endl;
            cout << kShotgunAmmo << ": shotgun ammo" << endl << endl;

            cout << "Items" << endl;
            cout << "-----" << endl;
            cout << kLife << ": life" << endl;
            cout << kWood << ": wood" << endl;
            cout << kSerum << ": serum" << endl << endl;

            cout << "Keys/Doors" << endl;
            cout << "--------------" << endl;
            cout << "blue: " << kBlueKey << "/" << kBlueDoor << endl;
            cout << "green: " << kGreenKey << "/" << kGreenDoor << endl;
            cout << "cyan: " << kCyanKey << "/" << kCyanDoor << endl;
            cout << "red: " << kRedKey << "/" << kRedDoor << endl;
            cout << "magenta: " << kMagentaKey << "/" << kMagentaDoor << endl;
            cout << "brown: " << kBrownKey << "/" << kBrownDoor << endl;
            cout << "yellow: " << kYellowKey << "/" << kYellowDoor << endl << endl;

            cout << "-------" << endl;
            cout << kPlayerStart << ": player start" << endl;
            cout << kZombie << ": zombies" << endl;
            cout << kLeftShootingCreature << kRightShootingCreature << ": left and right shooting creatures" << endl;
            cout << kDoor << ": unlocked door" << endl;
            cout << kCabinet << ": cabinet" << endl;
        }

        void GameplayEditorState::Save()
        {
            m_pStateMachine->m_pLevel->SaveLevel();
        }

        bool GameplayEditorState::IsWall(char input)
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

        bool GameplayEditorState::IsDoor(char input)
        {
            switch (input)
            {
            case kDoor:
            case kBlueDoor:
            case kGreenDoor:
            case kCyanDoor:
            case kRedDoor:
            case kMagentaDoor:
            case kBrownDoor:
            case kYellowDoor:
                return true;
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
            case kBlueKey:
            case kGreenKey:
            case kCyanKey:
            case kRedKey:
            case kMagentaKey:
            case kBrownKey:
            case kYellowKey:
                /*
                case kBlueDoor:
                case kGreenDoor:
                case kCyanDoor:
                case kRedDoor:
                case kMagentaDoor:
                case kBrownDoor:
                case kYellowDoor:
                */
            case kZombie:
            case kLeftShootingCreature:
            case kRightShootingCreature:
            case kCabinet:
            case kPlayerStart:
            case kEmpty:
                return true;
            }
            return false;
        }

    }
}