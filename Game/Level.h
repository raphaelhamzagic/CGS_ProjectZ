#pragma once
#include <string>
#include <vector>

namespace projectz {
    namespace game {
        class PlaceableActor;

        class Level
        {
            char* m_pLevelBlueprint;
            char* m_pLevelGameplay;
            char* m_pLevelData;

            int m_height;
            int m_width;

            int* m_playerX;
            int* m_playerY;

            std::vector<PlaceableActor*> m_pActors;

        public:
            static constexpr char WALL = (char)219;
            static constexpr char WINDOW_H = (char)196;
            static constexpr char WINDOW_V = (char)179;

            Level(int* playerX, int* playerY);
            ~Level();

            bool Load(std::string levelName);
            void Draw();
            PlaceableActor* UpdateActors(int newPlayerX, int newPlayerY);

            bool IsSpace(int x, int y);
            bool IsWall(int x, int y);
            bool IsDoor(int x, int y);
            bool IsWindow(int x, int y);

            int GetHeight() { return m_height; }
            int GetWidth() { return m_width; }


        private:
            bool Convert();
            int GetIndexFromCoordinates(int x, int y);
            char GetRoom(int x, int y);
        };
    }
}