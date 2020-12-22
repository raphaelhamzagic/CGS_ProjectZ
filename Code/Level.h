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
    bool Update(bool processInput);
    void Draw();

private:
    void Build(const std::vector<char> &blueprintLayer, const std::vector<char> &gameplayLayer);
    int MapIndexGet(int x, int y);
    void ProcessInput();
};

