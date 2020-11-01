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
            int m_height;
            int m_width;

            std::vector<PlaceableActor*> m_pActors;

        public:
            Level();
            ~Level();

            bool Load(std::string levelName, int* playerX, int* playerY);
            void Draw();
            PlaceableActor* UpdateActors(int x, int y);

            bool IsSpace(int x, int y);
            bool IsWall(int x, int y);

            int GetHeight() { return m_height; }
            int GetWidth() { return m_width; }

            static constexpr char WAL = (char)219;

        private:
            bool Convert(int* playerX, int* playerY);
            int GetIndexFromCoordinates(int x, int y);
        };
    }
}