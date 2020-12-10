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
    void Convert(char* blueprintLayer, char* gameplayLayer);
};

