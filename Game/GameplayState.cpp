#include <algorithm>
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "GameplayState.h"
#include "Ammo.h"
#include "AudioManager.h"
#include "Door.h"
#include "FireWeapon.h"
#include "Gun.h"
#include "HealthKit.h"
#include "Key.h"
#include "Map.h"
#include "MapChars.h"
#include "Point.h"
#include "SpittingCreature.h"
#include "StateMachineExampleGame.h"
#include "Utility.h"
#include "Zombie.h"

namespace projectz 
{
    namespace game 
    {
        constexpr int kArrowInput = 224;
        constexpr int kLeftArrow = 75;
        constexpr int kRightArrow = 77;
        constexpr int kUpArrow = 72;
        constexpr int kDownArrow = 80;
        constexpr int kEscape = 27;
        constexpr int kSpaceBar = 32;

        GameplayState::GameplayState(StateMachineExampleGame* pOwner)
            : m_pOwner(pOwner)
            , m_pMap(nullptr)
            , m_pPlayer(nullptr)
            , m_isMapLoaded(false)
            , m_currentLevel(0)
            , m_beatLevel(false)
            , m_skipFrameCount(0)
            , m_isPlayerHit(false)
        {
            m_LevelNames.push_back("Level1.txt");
            // m_LevelNames.push_back("Level2.txt");
            // m_LevelNames.push_back("Level3.txt");
        }

        void GameplayState::Unload()
        {
            if (m_pMap)
            {
                delete m_pMap;
                m_pMap = nullptr;
                m_isMapLoaded = false;
            }

            if (m_pPlayer)
            {
                delete m_pPlayer;
                m_pPlayer = nullptr;
            }

            while (!m_actors.empty())
            {
                delete m_actors.back();
                m_actors.pop_back();
            }
        }

        GameplayState::~GameplayState()
        {
            Unload();
        }

        void GameplayState::Load()
        {
            Unload();

            m_pMap = new Map;
            Point playerPosition;
            m_isMapLoaded = m_pMap->Load(m_LevelNames.at(m_currentLevel), m_actors, playerPosition);
            m_pPlayer = new Player{ playerPosition.x, playerPosition.y, MapChars::PlayerAliveRight, MapChars::PlayerAliveLeft, MapChars::PlayerAliveUp, MapChars::PlayerAliveDown, MapChars::PlayerDead };
        }

        void GameplayState::Enter()
        {
            Load();
        }

        bool GameplayState::Update(bool processInput)
        {
            if (!m_isMapLoaded)
            {
                return true;
            }

            if (processInput && !m_beatLevel && m_pPlayer->IsActive() && m_pPlayer->IsAlive())
            {
                m_isPlayerHit = false;

                int input = _getch();
                int arrowInput = 0;
                int newPlayerX = m_pPlayer->GetXPosition();
                int newPlayerY = m_pPlayer->GetYPosition();

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
                else if ((char)input == 'Z' || (char)input == 'z')
                {
                    m_pPlayer->DropKey();
                }
                else if (input == kSpaceBar)
                {
                    PlayerShoot();
                }
                else if (input == kEscape)
                {
                    m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
                    return false;
                }

                if (m_pPlayer->GetXPosition() != newPlayerX || m_pPlayer->GetYPosition() != newPlayerY)
                {
                    UpdatePlayer(newPlayerX, newPlayerY);
                }
                UpdateActors();
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

            if (!m_pPlayer->IsAlive())
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


        void GameplayState::UpdatePlayer(const int newPlayerX, const int newPlayerY)
        {
            PlaceableActor* collidedActor = nullptr;
            for (auto actor = m_actors.begin(); actor != m_actors.end(); ++actor)
            {
                if ((*actor)->GetXPosition() == newPlayerX && (*actor)->GetYPosition() == newPlayerY)
                {
                    collidedActor = (*actor);
                    break;
                }
            }

            if (collidedActor != nullptr && collidedActor->IsActive())
            {
                switch (collidedActor->GetType())
                {
                    case ActorType::Door:
                    {
                        Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
                        assert(collidedDoor);
                        if (collidedDoor->IsLocked())
                        {
                            if (m_pPlayer->HasKey(collidedDoor->GetColor()))
                            {
                                collidedDoor->Open();
                                m_pPlayer->UseKey();
                                m_pPlayer->SetPosition(newPlayerX, newPlayerY);
                                AudioManager::GetInstance()->PlayDoorOpenSound();
                                if (collidedDoor->GetColor() == ActorColor::Yellow)
                                {
                                    m_beatLevel = true;
                                }
                            }
                            else
                            {
                                m_pPlayer->SetDirection(newPlayerX - m_pPlayer->GetXPosition(), newPlayerY - m_pPlayer->GetYPosition());
                                AudioManager::GetInstance()->PlayDoorClosedSound();
                            }
                        }
                        else
                        {
                            m_pPlayer->SetPosition(newPlayerX, newPlayerY);
                        }
                        break;
                    }
                    case ActorType::Zombie:
                    {
                        Zombie* collidedEnemy = dynamic_cast<Zombie*>(collidedActor);
                        assert(collidedEnemy);
                        m_pPlayer->TakeDamage();
                        m_isPlayerHit = true;
                        AudioManager::GetInstance()->PlayLoseLivesSound();
                        break;
                    }
                    case ActorType::Key:
                    {
                        Key* collidedKey = dynamic_cast<Key*>(collidedActor);
                        assert(collidedKey);
                        if (m_pPlayer->HasKey())
                        {
                            m_pPlayer->SetDirection(newPlayerX - m_pPlayer->GetXPosition(), newPlayerY - m_pPlayer->GetYPosition());
                            AudioManager::GetInstance()->PlayDoorClosedSound();
                        }
                        else
                        {
                            m_pPlayer->PickupKey(collidedKey);
                            collidedKey->Remove();
                            m_pPlayer->SetPosition(newPlayerX, newPlayerY);
                            AudioManager::GetInstance()->PlayKeyPickupSound();
                        }
                        break;
                    }
                    case ActorType::Gun:
                    {
                        FireWeapon* colliedGun = dynamic_cast<FireWeapon*>(collidedActor);
                        assert(colliedGun);
                        m_pPlayer->PickupGun(colliedGun);
                        colliedGun->Remove();
                        m_pPlayer->SetPosition(newPlayerX, newPlayerY);
                        AudioManager::GetInstance()->PlayGunPickupSound();
                        break;
                    }
                    case ActorType::GunAmmo:
                    {
                        Ammo* collidedAmmo = dynamic_cast<Ammo*>(collidedActor);
                        assert(collidedAmmo);
                        if (m_pPlayer->HasGun())
                        {
                            m_pPlayer->PickupGunAmmo(collidedAmmo);
                            collidedAmmo->Remove();
                            m_pPlayer->SetPosition(newPlayerX, newPlayerY);
                            AudioManager::GetInstance()->PlayGunAmmoPickupSound();
                        }
                        else
                        {
                            m_pPlayer->SetDirection(newPlayerX - m_pPlayer->GetXPosition(), newPlayerY - m_pPlayer->GetYPosition());
                            AudioManager::GetInstance()->PlayDoorClosedSound();
                        }
                        break;
                    }
                    case ActorType::HealthKit:
                    {
                        HealthKit* collidedHealthKit = dynamic_cast<HealthKit*>(collidedActor);
                        assert(collidedHealthKit);
                        m_pPlayer->PickupHealthKit();
                        collidedHealthKit->Remove();
                        m_pPlayer->SetPosition(newPlayerX, newPlayerY);
                        AudioManager::GetInstance()->PlayDoorOpenSound();
                    }
                }
            }
            else if (m_pMap->IsWall(newPlayerX, newPlayerY))
            {
                m_pPlayer->SetDirection(newPlayerX - m_pPlayer->GetXPosition(), newPlayerY - m_pPlayer->GetYPosition());
                AudioManager::GetInstance()->PlayWallHitSound();
            }
            else
            {
                m_pPlayer->SetPosition(newPlayerX, newPlayerY);
            }
        }

        void GameplayState::PlayerShoot()
        {
            if (m_pPlayer->ShootFireWeapon())
            {
                bool hit = false;
                
                int projectileX = m_pPlayer->GetXPosition() + m_pPlayer->GetXDirection();
                int projectileY = m_pPlayer->GetYPosition() + m_pPlayer->GetYDirection();
                do
                {
                    if (m_pMap->IsEmpty(projectileX, projectileY))
                    {
                        PlaceableActor* actor = GetActorAtPosition(projectileX, projectileY);
                        if (actor != nullptr && actor->IsActive())
                        {
                            if (actor->GetType() == ActorType::Zombie || actor->GetType() == ActorType::SpittingCreature)
                            {
                                HitEnemy(actor, m_pPlayer->GetXDirection(), m_pPlayer->GetYDirection());
                            }
                            hit = true;
                        }
                        else
                        {
                            projectileX += m_pPlayer->GetXDirection();
                            projectileY += m_pPlayer->GetYDirection();
                        }
                    }
                    else
                    {
                        hit = true;
                    }
                } while (!hit);
            }
        }

        void GameplayState::HitEnemy (PlaceableActor* pEnemy, const int directionX, const int directionY)
        {
            pEnemy->TakeDamage();
            if (pEnemy->GetType() == ActorType::Zombie)
            {
                int newX = pEnemy->GetXPosition() + directionX;
                int newY = pEnemy->GetYPosition() + directionY;
                PlaceableActor* actor = GetActorAtPosition(newX, newY);
                if (actor != nullptr && actor->IsActive())
                {
                    if (actor->GetType() == ActorType::Zombie)
                    {
                        HitEnemy(actor, directionX, directionY);
                        pEnemy->SetPosition(newX, newY);
                    }
                }
                else
                {
                    pEnemy->SetPosition(newX, newY);
                }
            }          
        }

        void GameplayState::UpdateActors()
        {
            for (auto actor = m_actors.begin(); actor != m_actors.end(); ++actor)
            {
                if ((*actor)->IsActive())
                {
                    bool hasHitPlayer{ false };

                    if ((*actor)->GetType() == ActorType::Zombie)
                    {
                        Zombie* zombie = dynamic_cast<Zombie*>(*actor);
                        std::vector<Point> positionsAround{};
                        GetEmptyPositionsAround(zombie->GetXPosition(), zombie->GetYPosition(), positionsAround);
                        hasHitPlayer = zombie->Update(m_pPlayer->GetXPosition(), m_pPlayer->GetYPosition(), positionsAround);
                    }
                    else if ((*actor)->GetType() == ActorType::SpittingCreature)
                    {
                        std::vector<char> playerRoomsOut;
                        m_pMap->GetSurroundingRoomsFromPosition(m_pPlayer->GetXPosition(), m_pPlayer->GetYPosition(), playerRoomsOut);
                        char creatureRoom = m_pMap->GetRoomAtPosition((*actor)->GetXPosition(), (*actor)->GetYPosition());
                        auto found = std::find(playerRoomsOut.begin(), playerRoomsOut.end(), creatureRoom);
                        bool isPlayerInRoom = (found != playerRoomsOut.end());
                        SpittingCreature* spittingCreature = dynamic_cast<SpittingCreature*>(*actor);
                        hasHitPlayer = spittingCreature->Update(m_pPlayer->GetXPosition(), m_pPlayer->GetYPosition(), this, isPlayerInRoom);
                    }

                    if (hasHitPlayer && !m_isPlayerHit)
                    {
                        m_pPlayer->TakeDamage();
                        AudioManager::GetInstance()->PlayLoseLivesSound();
                    }
                }
            }
        }

        bool GameplayState::IsPositionEmpty(int x, int y)
        {
            bool result = false;
            if (m_pMap->IsEmpty(x, y))
            {
                if (m_pPlayer->GetXPosition() != x || m_pPlayer->GetYPosition() != y)
                {
                    PlaceableActor* actor = GetActorAtPosition(x, y);
                    result = (actor == nullptr);
                }
            }
            return result;
        }

        void GameplayState::GetEmptyPositionsAround(int x, int y, std::vector<Point>& positions)
        {
            std::vector<Point> surroundings = {
                Point(x - 1, y),
                Point(x + 1, y),
                Point(x, y - 1),
                Point(x, y + 1)
            };
            for (auto position = surroundings.begin(); position != surroundings.end(); ++position)
            {
                if (IsPositionEmpty(position->x, position->y))
                {
                    positions.push_back(*position);
                }
            }
        }


        PlaceableActor* GameplayState::GetActorAtPosition(int x, int y)
        {
            PlaceableActor* actorAtPosition{ nullptr };
            for (auto actor = m_actors.begin(); actor != m_actors.end(); ++actor)
            {
                if ((*actor)->IsActive())
                {
                    if ((*actor)->GetXPosition() == x && (*actor)->GetYPosition() == y)
                    {
                        actorAtPosition = *actor;
                        break;
                    }
                }
            }
            return actorAtPosition;
        }

        void GameplayState::Draw()
        {
            if (m_isMapLoaded)
            {
                system("cls");
                
                m_pMap->Draw(m_pPlayer->GetXPosition(), m_pPlayer->GetYPosition());

                HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
                DrawActors(console);
                DrawPlayer(console);          
                DrawHUD(console);
            }
        }

        void GameplayState::DrawPlayer(const HANDLE& console)
        {
            m_pPlayer->Draw(console);
        }

        void GameplayState::DrawActors(const HANDLE& console)
        {      
            std::vector<char> playerSurroundingRooms{};
            m_pMap->GetSurroundingRoomsFromPosition(m_pPlayer->GetXPosition(), m_pPlayer->GetYPosition(), playerSurroundingRooms);

            for (auto actor = m_actors.begin(); actor != m_actors.end(); ++actor)
            {
                if ((*actor)->IsActive())
                {
                    std::vector<char> actorSurroundingRooms{};
                    const int actorX = (*actor)->GetXPosition();
                    const int actorY = (*actor)->GetYPosition();
                    m_pMap->GetSurroundingRoomsFromPosition(actorX, actorY, actorSurroundingRooms);
                    for (char actorRoom : actorSurroundingRooms)
                    {
                        auto found = std::find(playerSurroundingRooms.begin(), playerSurroundingRooms.end(), actorRoom);
                        if (found != playerSurroundingRooms.end())
                        {
                            (*actor)->Draw(console);
                            break;
                        }
                    }
                }
            }
        }

        void GameplayState::DrawHUD(const HANDLE& console)
        {
            // Set the cursor to the end of the level
            COORD currentCursorPosition;
            currentCursorPosition.X = 0;
            currentCursorPosition.Y = m_pMap->GetHeight();
            SetConsoleCursorPosition(console, currentCursorPosition);

            std::cout << std::endl;

            // top border
            for (int i = 0; i < m_pMap->GetWidth(); i++)
            {
                std::cout << MapChars::Wall;
            }
            std::cout << std::endl;

            // left border
            std::cout << MapChars::Wall;

            std::cout << " wasd-move " << MapChars::Wall << " z-drop key " << MapChars::Wall;
            // cout << " $: " << m_player.GetMoney() << " " << Level::WALL;
            std::cout << " bullets: " << m_pPlayer->GetAmmo() << " " << MapChars::Wall;
            std::cout << " lives: " << m_pPlayer->GetLives() << " " << MapChars::Wall;
            std::cout << " key: ";
            if (m_pPlayer->HasKey())
            {
                m_pPlayer->GetKey()->Draw();
            }
            else
            {
                std::cout << " ";
            }

            // right border
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(console, &csbi);

            COORD pos;
            pos.X = m_pMap->GetWidth() - 1;
            pos.Y = csbi.dwCursorPosition.Y;
            SetConsoleCursorPosition(console, pos);

            std::cout << MapChars::Wall;
            std::cout << std::endl;

            // bottom border
            for (int i = 0; i < m_pMap->GetWidth(); i++)
            {
                std::cout << MapChars::Wall;
            }

            std::cout << std::endl;
        }
    }
}