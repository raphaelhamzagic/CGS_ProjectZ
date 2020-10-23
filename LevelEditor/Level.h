#pragma once
#include <string>

struct Point;

class Level
{
    static constexpr char kCursor = '_';

    std::string m_fileName;
    int m_height;
    int m_width;
    char* m_pBlueprint = nullptr;
    char* m_pElements = nullptr;

public:
    ~Level();
    int GetLevelHeight();
    int GetLevelWidth();
    
    bool LoadLevel();
    void NewLevel();
    bool SaveLevel();

    void SetLevelBlueprintCharacter(Point* pPosition, char character);
    void DrawLevelBlueprint(Point* pCursor);

private:
    void SetLevelDimensions();
    int GetIndexFromXY(int x, int y);
};
