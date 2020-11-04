#include "GameplayState.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "Door.h"
#include "Enemy.h"
#include "Goal.h"
#include "Key.h"
#include "Money.h"
#include "AudioManager.h"
#include "Utility.h"

#include "StateMachineExampleGame.h"

using namespace std;

namespace projectz {
    namespace game {

        constexpr int kArrowInput = 224;
        constexpr int kLeftArrow = 75;
        constexpr int kRightArrow = 77;
        constexpr int kUpArrow = 72;
        constexpr int kDownArrow = 80;
        constexpr int kEscape = 27;

        GameplayState::GameplayState(StateMachineExampleGame* pOwner)
            : m_pOwner(pOwner)
            , m_beatLevel(false)
            , m_skipFrameCount(0)
            , m_currentLevel(0)
            , m_pLevel(nullptr)
        {
            m_LevelNames.push_back("Level1.txt");
            // m_LevelNames.push_back("Level2.txt");
            // m_LevelNames.push_back("Level3.txt");
        }

        GameplayState::~GameplayState()
        {
            delete m_pLevel;
            m_pLevel = nullptr;
        }

        void GameplayState::Load()
        {
            if (m_pLevel)
            {
                delete m_pLevel;
                m_pLevel = nullptr;
                m_levelLoaded = false;
            }

            m_pLevel = new Level();
            m_levelLoaded = m_pLevel->Load(
                m_LevelNames.at(m_currentLevel),
                m_player.GetXPositionPointer(),
                m_player.GetYPositionPointer()
            );
        }

        void GameplayState::Enter()
        {
            Load();
        }

        bool GameplayState::Update(bool processInput)
        {
            if (!m_levelLoaded)
            {
                return true;
            }

            if (processInput && !m_beatLevel)
            {
                int input = _getch();
                int arrowInput = 0;
                int newPlayerX = m_player.GetXPosition();
                int newPlayerY = m_player.GetYPosition();

                if (input == kArrowInput)
                {
                    arrowInput = _getch();
                }

                if ((input == kArrowInput && arrowInput == kLeftArrow) ||
                    (char)input == 'A' || (char)input == 'a')
                {
                    newPlayerX--;
                }
                else if ((input == kArrowInput && arrowInput == kRightArrow) ||
                    (char)input == 'D' || (char)input == 'd')
                {
                    newPlayerX++;
                }
                else if ((input == kArrowInput && arrowInput == kUpArrow) ||
                    (char)input == 'W' || (char)input == 'w')
                {
                    newPlayerY--;
                }
                else if ((input == kArrowInput && arrowInput == kDownArrow) ||
                    (char)input == 'S' || (char)input == 's')
                {
                    newPlayerY++;
                }
                else if (input == kEscape)
                {
                    m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
                }
                else if ((char)input == 'Z' || (char)input == 'z')
                {
                    m_player.DropKey();
                }

                if (newPlayerX != m_player.GetXPosition() || newPlayerY != m_player.GetYPosition())
                {
                    HandleCollision(newPlayerX, newPlayerY);
                }
            }

            if (m_beatLevel)
            {
                ++m_skipFrameCount;
                if (m_skipFrameCount > kFramesToSkip)
                {
                    m_beatLevel = false;
                    m_skipFrameCount = 0;

                    ++m_currentLevel;
                    if (m_currentLevel == m_LevelNames.size())
                    {
                        Utility::WriteHighScore(m_player.GetMoney());
                        AudioManager::GetInstance()->PlayWinSound();
                        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
                    }
                    else
                    {
                        Load();
                    }
                }
            }

            return false;
        }

        void GameplayState::Draw()
        {
            if (m_levelLoaded)
            {
                HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
                system("cls");

                m_pLevel->Draw(m_player.GetXPosition(), m_player.GetYPosition());

                // Set cursor position for player
                COORD actorCursorPosition;
                actorCursorPosition.X = m_player.GetXPosition();
                actorCursorPosition.Y = m_player.GetYPosition();
                SetConsoleCursorPosition(console, actorCursorPosition);
                m_player.Draw();

                // Set the cursor to the end of the level
                COORD currentCursorPosition;
                currentCursorPosition.X = 0;
                currentCursorPosition.Y = m_pLevel->GetHeight();
                SetConsoleCursorPosition(console, currentCursorPosition);

                DrawHUD(console);
            }
        }
   

        void GameplayState::HandleCollision(int newPlayerX, int newPlayerY)
        {
            PlaceableActor* collidedActor = m_pLevel->UpdateActors(newPlayerX, newPlayerY);
            if (collidedActor != nullptr && collidedActor->IsActive())
            {
                switch (collidedActor->GetType())
                {
                case ActorType::Door:
                {
                    Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
                    if (!collidedDoor->IsOpen())
                    {
                        if (m_player.HasKey(collidedDoor->GetColor()))
                        {
                            collidedDoor->Open();
                            collidedDoor->Remove();
                            m_player.UseKey();
                            m_player.SetPosition(newPlayerX, newPlayerY);
                            AudioManager::GetInstance()->PlayDoorOpenSound();
                        }
                        else
                        {
                            AudioManager::GetInstance()->PlayDoorClosedSound();
                        }
                    }
                    else
                    {
                        m_player.SetPosition(newPlayerX, newPlayerY);
                    }
                    break;
                }
                case ActorType::Enemy:
                {
                    Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
                    assert(collidedEnemy);
                    collidedEnemy->Remove();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    m_player.DecrementLives();
                    AudioManager::GetInstance()->PlayLoseLivesSound();
                    if (m_player.GetLives() < 0)
                    {
                        AudioManager::GetInstance()->PlayLoseSound();
                        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
                    }
                    break;
                }
                case ActorType::Goal:
                {
                    Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
                    assert(collidedGoal);
                    collidedGoal->Remove();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    m_beatLevel = true;
                    break;
                }
                case ActorType::Key:
                {
                    Key* collidedKey = dynamic_cast<Key*>(collidedActor);
                    assert(collidedKey);
                    if (!m_player.HasKey())
                    {
                        m_player.PickupKey(collidedKey);
                        collidedKey->Remove();
                        m_player.SetPosition(newPlayerX, newPlayerY);
                        AudioManager::GetInstance()->PlayKeyPickupSound();
                    }
                    break;
                }
                case ActorType::Money:
                {
                    Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
                    assert(collidedMoney);
                    collidedMoney->Remove();
                    m_player.AddMoney(collidedMoney->GetWorth());
                    AudioManager::GetInstance()->PlayMoneySound();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    break;
                }
                }
            }
            else if (m_pLevel->IsSpace(newPlayerX, newPlayerY))
            {
                m_player.SetPosition(newPlayerX, newPlayerY);
            }
            else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
            {
                // wall collision, do nothing
            }
        }

        void GameplayState::DrawHUD(const HANDLE& console)
        {
            cout << endl;

            // top border
            for (int i = 0; i < m_pLevel->GetWidth(); i++)
            {
                cout << Level::WALL;
            }
            cout << endl;

            // left border
            cout << Level::WALL;

            cout << " wasd-move " << Level::WALL << " z-drop key " << Level::WALL;
            cout << " $: " << m_player.GetMoney() << " " << Level::WALL;
            cout << " lives: " << m_player.GetLives() << " " << Level::WALL;
            cout << " key: ";
            if (m_player.HasKey())
            {
                m_player.GetKey()->Draw();
            }
            else
            {
                cout << " ";
            }

            // right border
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(console, &csbi);

            COORD pos;
            pos.X = m_pLevel->GetWidth() - 1;
            pos.Y = csbi.dwCursorPosition.Y;
            SetConsoleCursorPosition(console, pos);

            cout << Level::WALL;
            cout << endl;

            // bottom border
            for (int i = 0; i < m_pLevel->GetWidth(); i++)
            {
                cout << Level::WALL;
            }
        }
    }
}