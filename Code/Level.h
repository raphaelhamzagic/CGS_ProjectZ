#pragma once
#include <iostream>
#include <vector>

class GameObject;
class Player;

class Level
{
    int m_width;
    int m_height;
    std::vector<GameObject*>* m_pGameObjects;
    Player* m_pPlayer;


public:
    Level();
    bool Load(std::string levelFileName);
    bool Update(bool processInput);
    void Draw();
    GameObject* GameObjectGet(int x, int y);

private:
    void Build(const std::vector<char> &blueprintLayer, const std::vector<char> &gameplayLayer);
    int MapIndexGet(int x, int y);
};

