#include "GameplayState.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "Ammo.h"
#include "AudioManager.h"
#include "Door.h"
#include "FireWeapon.h"
#include "Goal.h"
#include "Gun.h"
#include "HealthKit.h"
#include "Key.h"
#include "Point.h"
#include "StateMachineExampleGame.h"
#include "Utility.h"
#include "Zombie.h"

using namespace std;

namespace projectz {
    namespace game {

        constexpr int kArrowInput = 224;
        constexpr int kLeftArrow = 75;
        constexpr int kRightArrow = 77;
        constexpr int kUpArrow = 72;
        constexpr int kDownArrow = 80;
        constexpr int kEscape = 27;
        constexpr int kSpaceBar = 32;

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

            m_pLevel = new Level(m_player.GetXPositionPointer(), m_player.GetYPositionPointer());
            m_levelLoaded = m_pLevel->Load(m_LevelNames.at(m_currentLevel));
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

            if (processInput && !m_beatLevel && m_player.IsAlive())
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
                else if (input == kSpaceBar)
                {
                    PlayerShoot();
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
                        // TODO 
                        Utility::WriteHighScore(100);
                        AudioManager::GetInstance()->PlayWinSound();
                        m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
                    }
                    else
                    {
                        Load();
                    }
                }
            }

            if (!m_player.IsAlive())
            {
                ++m_skipFrameCount;
                if (m_skipFrameCount > kFramesToSkip)
                {
                    m_skipFrameCount = 0;
                    AudioManager::GetInstance()->PlayLoseSound();
                    system("pause");
                    m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
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

                m_pLevel->Draw();

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
                        if (collidedDoor->IsLocked())
                        {
                            if (m_player.HasKey(collidedDoor->GetColor()))
                            {
                                collidedDoor->Open();
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
                    case ActorType::Zombie:
                    {
                        Zombie* collidedEnemy = dynamic_cast<Zombie*>(collidedActor);
                        assert(collidedEnemy);
                        m_player.TakeDamage();
                        AudioManager::GetInstance()->PlayLoseLivesSound();                        
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
                    case ActorType::Gun:
                    {
                        FireWeapon* colliedGun = dynamic_cast<FireWeapon*>(collidedActor);
                        assert(colliedGun);
                        m_player.PickupGun(colliedGun);
                        colliedGun->Remove();
                        m_player.SetPosition(newPlayerX, newPlayerY);
                        AudioManager::GetInstance()->PlayGunPickupSound();
                        break;
                    }
                    case ActorType::GunAmmo:
                    {
                        Ammo* collidedAmmo = dynamic_cast<Ammo*>(collidedActor);
                        assert(collidedAmmo);
                        if (m_player.HasGun())
                        {
                            m_player.PickupGunAmmo(collidedAmmo);
                            collidedAmmo->Remove();
                            m_player.SetPosition(newPlayerX, newPlayerY);
                            AudioManager::GetInstance()->PlayGunAmmoPickupSound();
                        }
                        else
                        {
                            AudioManager::GetInstance()->PlayDoorClosedSound();
                        }
                        break;
                    }
                    case ActorType::HealthKit:
                    {
                        HealthKit* collidedHealthKit = dynamic_cast<HealthKit*>(collidedActor);
                        assert(collidedHealthKit);
                        m_player.PickupHealthKit();
                        collidedHealthKit->Remove();
                        m_player.SetPosition(newPlayerX, newPlayerY);
                        // TODO change sound
                        AudioManager::GetInstance()->PlayDoorOpenSound(); 
                    }
                }
            }
            else if (m_pLevel->IsSpace(newPlayerX, newPlayerY))
            {
                m_player.SetPosition(newPlayerX, newPlayerY);
            }
            else if (m_pLevel->IsWall(newPlayerX, newPlayerY))
            {
                int playerX = m_player.GetXPosition();
                int directionX = 0;
                if (newPlayerX != playerX)
                {
                    if (newPlayerX > playerX)
                    {
                        directionX = 1;
                    }
                    else
                    {
                        directionX = -1;
                    }
                }

                int playerY = m_player.GetYPosition();
                int directionY = 0;
                if (newPlayerY != playerY)
                {
                    if (newPlayerY > playerY)
                    {
                        directionY = 1;
                    }
                    else
                    {
                        directionY = -1;
                    }
                }

                if (directionX != 0 || directionY != 0)
                {
                    m_player.SetDirection(directionX, directionY);
                }
                
                AudioManager::GetInstance()->PlayWallHitSound();
            }
        }

        void GameplayState::PlayerShoot()
        {
            if (m_player.ShootFireWeapon())
            {
                bool hit = false;
                Point position = m_player.GetPosition() + m_player.GetDirection();
                do
                {
                    if (m_pLevel->IsSpace(position.x, position.y))
                    {
                        PlaceableActor* zombieActor = m_pLevel->GetActorAtPosition(position);
                        if (zombieActor != nullptr && zombieActor->IsActive())
                        {
                            zombieActor->TakeDamage(&m_player.GetDirection());
                            hit = true;
                        }
                        else
                        {
                            position = position + m_player.GetDirection();
                        }
                    }
                    else
                    {
                        hit = true;
                    }
                } while (!hit);
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
            // cout << " $: " << m_player.GetMoney() << " " << Level::WALL;
            cout << " bullets: " << m_player.GetAmmo() << " " << Level::WALL;
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

            cout << endl;
        }
    }
}