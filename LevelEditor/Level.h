#pragma once
#include <string>

class Point;

class Level
{
    static constexpr char kCursor = '_';

    std::string m_fileName;
    int m_height;
    int m_width;
    char* m_pBlueprint = nullptr;
    char* m_pElements = nullptr;

public:
    bool Load();
    void New();
    bool Save();
    void DrawBlueprint(Point* pCursor);
    int GetHeight();
    int GetWidth();
    void SetBlueprintCharacter(Point* pPosition, char character);

private:
    void SetLevelDimensions();
    int GetIndexFromXY(int x, int y);
};
