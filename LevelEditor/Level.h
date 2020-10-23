#pragma once
#include <string>

struct Point;

class Level
{
    static constexpr int kLevelWidth = 100;
    static constexpr int klevelHeight = 25;

    std::string m_fileName = "UntitledLevel";
    int m_height;
    int m_width;
    char* m_pBlueprint = nullptr;
    char* m_pElements = nullptr;

public:
    Level();
    ~Level();
    int GetLevelHeight();
    int GetLevelWidth();
    char* GetLevelBlueprint();
    char* GetLevelElements();
    std::string GetLevelFilename();

    bool LoadLevel();
    void NewLevel();
    bool SaveLevel();

    int GetIndexFromXY(int x, int y);

private:
    void SetLevelDimensions();
};
