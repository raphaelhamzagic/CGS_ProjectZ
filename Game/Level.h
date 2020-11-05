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

            std::vector<PlaceableActor*> m_pActors;

        public:
            Level();
            ~Level();

            bool Load(std::string levelName, int* playerX, int* playerY);
            void Draw(int playerX, int playerY);
            PlaceableActor* UpdateActors(int x, int y);

            bool IsSpace(int x, int y);
            bool IsWall(int x, int y);

            int GetHeight() { return m_height; }
            int GetWidth() { return m_width; }

            static constexpr char WALL = (char)219;
            static constexpr char WINDOW_H = (char)196;
            static constexpr char WINDOW_V = (char)179;


        private:
            bool Convert(int* playerX, int* playerY);
            int GetIndexFromCoordinates(int x, int y);
            char GetRoom(int x, int y);
        };
    }
}