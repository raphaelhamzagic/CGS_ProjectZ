#include <iostream>
#include <fstream>
#include <Windows.h>
#include <assert.h>
#include "Door.h"
#include "Goal.h"
#include "Key.h"
#include "Level.h"
#include "Player.h"
#include "PlaceableActor.h"
#include "Point.h"
#include "Zombie.h"

using namespace std;

namespace projectz {
    namespace game {

        Level::Level(int* playerX, int* playerY)
            : m_pLevelBlueprint(nullptr)
            , m_pLevelGameplay(nullptr)
            , m_pLevelData(nullptr)
            , m_height(0)
            , m_width(0)
            , m_playerX(playerX)
            , m_playerY(playerY)
        {
        }

        Level::~Level()
        {
            /*
            * TODO, crashing when running this code
            if (m_pLevelBlueprint != nullptr)
            {
                delete[] m_pLevelBlueprint;
                m_pLevelBlueprint = nullptr;
            }

            if (m_pLevelGameplay != nullptr)
            {
                delete[] m_pLevelGameplay;
                m_pLevelGameplay = nullptr;
            }

            if (m_pLevelData != nullptr)
            {
                delete[] m_pLevelData;
                m_pLevelData = nullptr;
            }
            */

            while (!m_pActors.empty())
            {
                delete m_pActors.back();
                m_pActors.pop_back();
            }
        }

        bool Level::Load(std::string levelName)
        {
            levelName.insert(0, "../Maps/");
            ifstream levelFile;
            levelFile.open(levelName);
            if (!levelFile)
            {
                cout << "Opening file failed!" << endl;
                return false;
            }
            else
            {
                constexpr int tempSize = 25;
                char temp[tempSize];

                levelFile.getline(temp, tempSize, '\n');
                m_width = atoi(temp);

                levelFile.getline(temp, tempSize, '\n');
                m_height = atoi(temp);

                std::streamsize levelSize = static_cast<std::streamsize>(m_width) * static_cast<std::streamsize>(m_height);
                m_pLevelBlueprint = new char[levelSize];
                m_pLevelGameplay = new char[levelSize];
                             
                levelFile.getline(m_pLevelBlueprint, levelSize+1, '\n');
                levelFile.getline(m_pLevelGameplay, levelSize+1, '\n');

                m_pLevelData = new char[levelSize];
                bool anyWarnings = Convert();
                if (anyWarnings)
                {
                    cout << "There were some warnings in the level data, see above." << endl;
                    system("pause");
                }
                return true;
            }
        }

        void Level::Draw()
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);
            char playerRoom = GetRoom(*m_playerX, *m_playerY);

            // Draw the level
            for (int y = 0; y < GetHeight(); y++)
            {
                for (int x = 0; x < GetWidth(); x++)
                {
                    int index = GetIndexFromCoordinates(x, y);
                    if (
                        m_pLevelBlueprint[index] == playerRoom
                        || 
                        IsWall(x, y)
                        ||
                        IsWindow(x, y)
                    )
                    {
                        cout << m_pLevelData[index];
                    }
                    else
                    {
                        cout << (char)176;
                    }
                }
                cout << endl;
            }

            COORD actorCursorPosition;

            // Draw the actors
            for (auto actor = m_pActors.begin(); actor != m_pActors.end(); actor++)
            {
                if ((*actor)->IsActive())
                {
                    if ((*actor)->GetType() == ActorType::Door
                        ||
                        GetRoom((*actor)->GetXPosition(), (*actor)->GetYPosition()) == playerRoom)
                    {
                        actorCursorPosition.X = (short)(*actor)->GetXPosition();
                        actorCursorPosition.Y = (short)(*actor)->GetYPosition();
                        SetConsoleCursorPosition(console, actorCursorPosition);
                        (*actor)->Draw();
                    }                    
                }
            }
        }

        bool Level::IsSpace(int x, int y)
        {
            return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
        }

        bool Level::IsWall(int x, int y)
        {
            return m_pLevelData[GetIndexFromCoordinates(x, y)] == WALL;
        }

        bool Level::IsDoor(int x, int y)
        {
            return m_pLevelBlueprint[GetIndexFromCoordinates(x, y)] == 'D';
            /*
            switch (m_pLevelData[GetIndexFromCoordinates(x, y)])
            {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'Z':
                case 'Y':
                case 'X':
                case 'W':
                case 'V':
                case 'U':
                case 'T':
                    return true;
            }
            return false;
            */
        }

        bool Level::IsWindow(int x, int y)
        {
            char c = m_pLevelData[GetIndexFromCoordinates(x, y)];
            return (c == WINDOW_H || c == WINDOW_V);
        }

        PlaceableActor* Level::GetActorAtPosition(Point position)
        {
            PlaceableActor* pActor = nullptr;
            for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
            {
                if ((*actor)->GetPosition() == position)
                {
                    assert(pActor == nullptr);
                    pActor = (*actor);
                }               
            }
            return pActor;
        }

        bool Level::Convert()
        {
            bool anyWarnings = false;

            for (int y = 0; y < m_height; y++)
            {
                for (int x = 0; x < m_width; x++)
                {
                    int index = GetIndexFromCoordinates(x, y);

                    switch (m_pLevelBlueprint[index])
                    {
                        case '+':
                        case '-':
                        case '|':
                            m_pLevelData[index] = WALL;
                            break;

                        case 'D':
                        case 'W':
                            m_pLevelData[index] = ' ';
                            break;

                        case 'a':
                        case 'b':
                        case 'c':
                        case 'd':
                        case 'e':
                        case 'f':
                        case 'g':
                        case 'h':
                        case 'i':
                        case 'j':
                        case 'k':
                        case 'l':
                        case 'm':
                        case 'n':
                            m_pLevelData[index] = ' ';
                            break;

                        default:
                            cout << "Invalid character in level file: " << m_pLevelBlueprint[index] << endl;
                            anyWarnings = true;
                            break;
                    }

                    switch (m_pLevelGameplay[index])
                    {
                        // skip walls and spaces
                        case '+':
                        case '-':
                        case '|':
                        case ' ':
                            break;

                        // TODO:
                        // weapons
                        case '1':
                        case '2':
                        // ammo
                        case '.':
                        case '*':
                        // items
                        case 'l':
                        case 'w':
                        case 'x':
                            break;

                        // enemies
                        case 'z':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Zombie(x, y, this));
                            break;

                        case '<':
                        case '>':
                        // cabinet
                        case 'P':
                            break;

                        // windows
                        case 'M':
                            m_pLevelData[index] = WINDOW_H;
                            break;

                        case 'N':
                            m_pLevelData[index] = WINDOW_V;
                            break;                            

                        // keys
                        case 'a':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::Brown));
                            break;
                        case 'b':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::LightBlue));
                            break;
                        case 'c':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::LightCyan));
                            break;
                        case 'd':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::LightGreen));
                            break;
                        case 'e':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::Magenta));
                            break;
                        case 'f':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::LightRed));
                            break;
                        case 'g':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Key(x, y, ActorColor::Yellow));
                            break;

                        // Doors
                        case 'A':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, false, ActorColor::Brown, ActorColor::Brown));
                            break;
                        case 'Z':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, false, ActorColor::Brown, ActorColor::Brown));
                            break;

                        case 'B':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, true, ActorColor::Brown, ActorColor::LightBlue));
                            break;
                        case 'Y':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, true, ActorColor::Brown, ActorColor::LightBlue));
                            break;

                        case 'C':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, true, ActorColor::Brown, ActorColor::LightCyan));
                            break;
                        case 'X':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, true, ActorColor::Brown, ActorColor::LightCyan));
                            break;

                        case 'D':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, true, ActorColor::Brown, ActorColor::LightGreen));
                            break;
                        case 'W':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, true, ActorColor::Brown, ActorColor::LightGreen));
                            break;

                        case 'E':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, true, ActorColor::Brown, ActorColor::Magenta));
                            break;
                        case 'V':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, true, ActorColor::Brown, ActorColor::Magenta));
                            break;

                        case 'F':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, true, ActorColor::Brown, ActorColor::LightRed));
                            break;
                        case 'U':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, true, ActorColor::Brown, ActorColor::LightRed));
                            break;

                        case 'G':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Horizontal, true, ActorColor::Brown, ActorColor::Yellow));
                            break;
                        case 'T':
                            m_pLevelData[index] = ' ';
                            m_pActors.push_back(new Door(x, y, ActorOrientation::Vertical, true, ActorColor::Brown, ActorColor::Yellow));
                            break;

                        case '@':
                            m_pLevelData[index] = ' ';
                            if (m_playerX != nullptr && m_playerY != nullptr)
                            {
                                *m_playerX = x;
                                *m_playerY = y;
                            }
                            break;

                        default:
                            cout << "Invalid character in level file: " << m_pLevelGameplay[index] << endl;
                            anyWarnings = true;
                            break;
                    }
                }
            }

            return anyWarnings;
        }

        int Level::GetIndexFromCoordinates(int x, int y)
        {
            return x + y * m_width;
        }

        PlaceableActor* Level::UpdateActors(int newPlayerX, int newPlayerY)
        {
            char newPlayerRoom = GetRoom(newPlayerX, newPlayerY);
            PlaceableActor* collidedActor = nullptr;
            
            for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
            {
                char actorRoom = GetRoom((*actor)->GetXPosition(), (*actor)->GetYPosition());
                if (actorRoom == newPlayerRoom)
                {
                    if ((*actor)->GetType() == ActorType::Zombie)
                    {
                        (*actor)->Update(this, newPlayerX, newPlayerY);
                    }
                    else
                    {
                        (*actor)->Update();
                    }
                    if (newPlayerX == (*actor)->GetXPosition() && newPlayerY == (*actor)->GetYPosition())
                    {
                        assert(collidedActor == nullptr);
                        collidedActor = (*actor);
                    }
                }     
            }

            return collidedActor;
        }

        char Level::GetRoom(int x, int y)
        {
            int index = GetIndexFromCoordinates(x, y);
            switch (m_pLevelBlueprint[index])
            {
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                    return m_pLevelBlueprint[index];
            }
            return ' ';
        }

    }
}