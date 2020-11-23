#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <Windows.h>

#include "Map.h"
#include "Door.h"
#include "Gun.h"
#include "GunAmmo.h"
#include "HealthKit.h"
#include "Key.h"
#include "MapChars.h"
#include "PlaceableActor.h"
#include "Player.h"
#include "Point.h"
#include "SpittingCreature.h"
#include "Zombie.h"

namespace projectz
{
    namespace game
    {
        Map::Map()
            : m_pBlueprintMap(nullptr)
            , m_pGameplayMap(nullptr)
            , m_width(0)
            , m_height(0)
        {
        }

        Map::~Map()
        {
            if (m_pGameplayMap != nullptr)
            {
                delete[] m_pGameplayMap;
                m_pGameplayMap = nullptr;
            }
            if (m_pBlueprintMap != nullptr)
            {
                delete[] m_pBlueprintMap;
                m_pBlueprintMap = nullptr;
            }
        }

        bool Map::Load(std::string levelFileName, std::vector<PlaceableActor*> &actorsOut, Point& playerInitialPositionOut)
        {
            if (m_pGameplayMap != nullptr)
            {
                delete[] m_pGameplayMap;
                m_pGameplayMap = nullptr;
            }

            if (m_pBlueprintMap != nullptr)
            {
                delete[] m_pBlueprintMap;
                m_pBlueprintMap = nullptr;
            }

            levelFileName.insert(0, "../Maps/");
            std::ifstream levelFile;
            levelFile.open(levelFileName);
            if (!levelFile)
            {
                std::cout << "Opening file failed!" << std::endl;
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
                char* pMapBlueprintLayer = new char[levelSize];
                levelFile.getline(pMapBlueprintLayer, levelSize + 1, '\n');

                char* pMapGameplayLayer = new char[levelSize];
                levelFile.getline(pMapGameplayLayer, levelSize + 1, '\n');

                levelFile.close();

                m_pGameplayMap = new char[levelSize];
                bool anyWarnings = Convert(pMapBlueprintLayer, pMapGameplayLayer, actorsOut, playerInitialPositionOut);
                if (anyWarnings)
                {
                    std::cout << "There were some warnings in the level data, see above." << std::endl;
                    system("pause");
                }
                return true;
            }
        }

        bool Map::Convert(const char* const pMapBlueprint, const char* const pMapGameplay, std::vector<PlaceableActor*>& actorsOut, Point& playerInitialPositionOut)
        {
            bool anyWarnings = false;
            std::streamsize levelSize = static_cast<std::streamsize>(m_width) * static_cast<std::streamsize>(m_height);
            m_pBlueprintMap = new char[levelSize] {};
            m_pGameplayMap = new char[levelSize] {};

            for (int y = 0; y < m_height; y++)
            {
                for (int x = 0; x < m_width; x++)
                {
                    int index = GetIndexFromCoordinates(x, y);

                    switch (pMapBlueprint[index])
                    {
                        case '+':
                        case '-':
                        case '|':
                            m_pBlueprintMap[index] = MapChars::Wall;
                            m_pGameplayMap[index] = MapChars::Wall;
                            break;
                        case 'D': // door
                        case 'W': // window
                            m_pBlueprintMap[index] = MapChars::Empty;
                            m_pGameplayMap[index] = MapChars::Empty;
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
                        case 'n': // rooms
                            m_pBlueprintMap[index] = pMapBlueprint[index];
                            m_pGameplayMap[index] = MapChars::Empty;
                            break;
                        default:
                            std::cout << "Invalid character in level file: " << pMapBlueprint[index] << std::endl;
                            anyWarnings = true;
                            break;
                    }

                    switch (pMapGameplay[index])
                    {
                        // skip walls and spaces
                        case '+':
                        case '-':
                        case '|':
                        case ' ':
                            break;

                        // weapons
                        case '1':
                            actorsOut.push_back(
                                new Gun{ x,y, MapChars::WeaponGun }
                            );
                            break;

                        case '2':
                            // TODO shotgun
                            break;

                        // ammo
                        case '.':
                            actorsOut.push_back(
                                new GunAmmo{ x, y, MapChars::AmmoGun }
                            );
                            break;
                        case '*':
                            // TODO shotgun ammo

                        // items
                        case 'l':
                            actorsOut.push_back(
                                new HealthKit{ x, y, MapChars::HealthKit, ActorColor::LightGreen }
                            );
                            break;

                        case 'w':
                            // TODO wood (block windows)
                        case 'x':
                            // TODO serum
                            break;

                        // enemies
                        case 'z':
                            actorsOut.push_back(
                                new Zombie{ x, y, MapChars::EnemyZombie }
                            );
                            break;
                        case '<':
                            actorsOut.push_back(
                                new SpittingCreature{ x, y, MapChars::EnemyGooSpittingLeft, MapChars::EnemyGooSpittingLeftProjectile, -1 }
                            );
                            break;
                        case '>':
                            actorsOut.push_back(
                                new SpittingCreature{ x, y, MapChars::EnemyGooSpittingRight, MapChars::EnemyGooSpittingRightProjectile, 1 }
                            );
                            break;

                        // cabinet (save progress)
                        case 'P':
                            break;

                        // windows
                        case 'M':
                            // tmp while window feature is not implemented
                            m_pGameplayMap[index] = MapChars::WindowHorizontal;
                            break;
                        case 'N':
                            // tmp while window feature is not implemented
                            m_pGameplayMap[index] = MapChars::WindowVertical;
                            break;

                        // keys
                        case 'a':
                        case 'b':
                        case 'c':
                        case 'd':
                        case 'e':
                        case 'f':
                        case 'g':
                        {
                            m_pGameplayMap[index] = MapChars::Empty;
                            std::unordered_map<char, ActorColor> keyColors{
                                {'a', ActorColor::Brown},
                                {'b', ActorColor::LightBlue},
                                {'c', ActorColor::LightCyan},
                                {'d', ActorColor::LightGreen},
                                {'e', ActorColor::Magenta},
                                {'f', ActorColor::LightRed},
                                {'g', ActorColor::Yellow}
                            };
                            actorsOut.push_back(
                                new Key{ x, y, MapChars::Key, keyColors[pMapGameplay[index]] }
                            );
                            break;
                        }
                        // Doors
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
                        {
                            std::unordered_map<char, DoorConfig> doorConfig{
                                {'A', {MapChars::DoorHorizontal, false, ActorColor::Brown, ActorColor::Brown}},
                                {'B', {MapChars::DoorHorizontal, true, ActorColor::LightBlue, ActorColor::Brown}},
                                {'C', {MapChars::DoorHorizontal, true, ActorColor::LightCyan, ActorColor::Brown}},
                                {'D', {MapChars::DoorHorizontal, true, ActorColor::LightGreen, ActorColor::Brown}},
                                {'E', {MapChars::DoorHorizontal, true, ActorColor::Magenta, ActorColor::Brown}},
                                {'F', {MapChars::DoorHorizontal, true, ActorColor::LightRed, ActorColor::Brown}},
                                {'G', {MapChars::DoorHorizontal, true, ActorColor::Yellow, ActorColor::Brown}},
                                {'Z', {MapChars::DoorVertical, false, ActorColor::Brown, ActorColor::Brown}},
                                {'Y', {MapChars::DoorVertical, true, ActorColor::LightBlue, ActorColor::Brown}},
                                {'X', {MapChars::DoorVertical, true, ActorColor::LightCyan, ActorColor::Brown}},
                                {'W', {MapChars::DoorVertical, true, ActorColor::LightGreen, ActorColor::Brown}},
                                {'V', {MapChars::DoorVertical, true, ActorColor::Magenta, ActorColor::Brown}},
                                {'U', {MapChars::DoorVertical, true, ActorColor::LightRed, ActorColor::Brown}},
                                {'T', {MapChars::DoorVertical, true, ActorColor::Yellow, ActorColor::Brown}}
                            };
                            m_pGameplayMap[index] = MapChars::Empty;
                            const DoorConfig& config = doorConfig[pMapGameplay[index]];
                            actorsOut.push_back(
                                new Door{ x, y, config.symbol, config.isLocked, config.lockedColor, config.unlockedColor }
                            );
                            break;
                        }
                        case '@':
                            m_pGameplayMap[index] = MapChars::Empty;
                            playerInitialPositionOut.x = x;
                            playerInitialPositionOut.y = y;
                            break;

                        default:
                            std::cout << "Invalid character in level file: " << pMapGameplay[index] << std::endl;
                            anyWarnings = true;
                            break;
                    }
                }
            }

            return anyWarnings;
        }

        char Map::GetRoomAtPosition(int x, int y)
        {            
            int index = GetIndexFromCoordinates(x, y);
            switch (m_pBlueprintMap[index])
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
                    return m_pBlueprintMap[index];
            }
            return MapChars::Empty;
        }

        void Map::GetSurroundingRoomsFromPosition(int x, int y, std::vector<char> &roomsOut)
        {
            std::vector<Point> surroundings = {
                Point(x - 1, y),
                Point(x + 1, y),
                Point(x, y - 1),
                Point(x, y + 1)
            };
            for (auto position = surroundings.begin(); position != surroundings.end(); ++position)
            {
                if (position->x > 0 && position->x <= m_width && position->y > 0 && position->y <= m_height)
                {
                    char room = GetRoomAtPosition(position->x, position->y);
                    if (room != MapChars::Empty)
                    {
                        auto found = std::find(roomsOut.begin(), roomsOut.end(), room);
                        if (found == roomsOut.end())
                        {
                            roomsOut.push_back(room);
                        }
                    }
                }
            }
        }

        bool Map::IsWall(int x, int y)
        {
            return m_pBlueprintMap[GetIndexFromCoordinates(x, y)] == MapChars::Wall;
        }

        bool Map::IsWindow(int x, int y)
        {
            char c = m_pGameplayMap[GetIndexFromCoordinates(x, y)];
            return (c == MapChars::WindowHorizontal || c == MapChars::WindowVertical);
        }

        bool Map::IsEmpty(int x, int y)
        {
            return m_pGameplayMap[GetIndexFromCoordinates(x, y)] == MapChars::Empty;
        }

        void Map::Draw(const int playerX, const int playerY)
        {
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console, (int)ActorColor::LightGray);

            std::vector<char> surroundingRooms{};
            GetSurroundingRoomsFromPosition(playerX, playerY, surroundingRooms);

            for (int y = 0; y < m_height; y++)
            {
                for (int x = 0; x < m_width; x++)
                {
                    char room = GetRoomAtPosition(x, y);
                    auto found = std::find(surroundingRooms.begin(), surroundingRooms.end(), room);
                    bool isPlayerRoom = (found != surroundingRooms.end());
                    if (IsWall(x, y) || IsWindow(x, y) || isPlayerRoom)
                    {
                        int index = GetIndexFromCoordinates(x, y);
                        std::cout << m_pGameplayMap[index];
                    }
                    else
                    {
                        std::cout << MapChars::Fog;
                    }
                }
                std::cout << std::endl;
            }
            COORD actorCursorPosition;
        }

        int Map::GetIndexFromCoordinates(const Point &p)
        {
            return p.x + p.y * m_width;
        }
        int Map::GetIndexFromCoordinates(const int& x, const int& y)
        {
            return x + y * m_width;
        }
    }
}

