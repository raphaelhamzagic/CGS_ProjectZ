#pragma once
#include <iostream>
#include <vector>

class GameObject;

class Level
{
    int m_width;
    int m_height;
    std::vector<GameObject*>* m_pGameObjects;

public:
    Level();
    bool Load(std::string levelFileName);
    void Draw();

private:
    void Build(char* blueprintLayer, char* gameplayLayer);
    void CharCopy(char* pOrigin, char* pDestination, int originIndex, int count, int destinationIndex);
    int MapIndexGet(int x, int y);
};

