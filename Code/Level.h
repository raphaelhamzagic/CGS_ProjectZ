#pragma once
#include <iostream>

class Level
{
    int m_width;
    int m_height;

public:
    Level();
    bool Load(std::string levelFileName);

private:
    void Build(char* blueprintLayer, char* gameplayLayer);
    void CopyChars(char* pOrigin, char* pDestination, int originIndex, int count, int destinationIndex);
};

