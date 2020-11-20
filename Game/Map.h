#pragma once
#include <string>
#include <vector>
#include "PlaceableActor.h"

namespace projectz 
{
    namespace game 
    {
        class Point;

        class Map
        {
            int m_width;
            int m_height;
            char *m_pBlueprintMap;
            char *m_pGameplayMap;
        public:
            Map();
            ~Map();

            bool Load(std::string levelFileName, std::vector<PlaceableActor*> &actorsOut, Point &playerInitialPositionOut);
            bool Convert(const char *const pMapBlueprint, const char *const pMapGameplay, std::vector<PlaceableActor*> &actorsOut, Point& playerInitialPositionOut);
            void Draw(const int playerX, const int playerY);
            char GetRoomAtPosition(int x, int y);
            void GetSurroundingRoomsFromPosition(int x, int y, std::vector<char> &roomsOut);

            bool IsWall(int x, int y);
            bool IsWindow(int x, int y);
            bool IsEmpty(int x, int y);

            int GetWidth() const { return m_width; };
            int GetHeight() const { return m_height; };

        private:
            int GetIndexFromCoordinates(const Point &p);
            int GetIndexFromCoordinates(const int &x, const int &y);
        };
    }
}


