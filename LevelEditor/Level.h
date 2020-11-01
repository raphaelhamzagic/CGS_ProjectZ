#pragma once
#include <string>

namespace projectz {
    namespace editor {
        struct Point;

        class Level
        {
            static constexpr int kLevelWidth = 100;
            static constexpr int klevelHeight = 25;

            std::string m_fileName;
            int m_height;
            int m_width;
            char* m_pLevelBlueprint = nullptr;
            char* m_pLevelGameplay = nullptr;

        public:
            ~Level();
            int GetLevelHeight();
            int GetLevelWidth();
            char* GetLevelBlueprint();
            char* GetLevelGameplay();
            std::string GetLevelFilename();

            bool LoadLevel();
            void NewLevel();
            bool SaveLevel();

            int GetIndexFromXY(int x, int y);
        };
    }
}