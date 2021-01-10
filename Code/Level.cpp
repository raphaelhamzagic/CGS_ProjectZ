#include <fstream>
// #include <iostream>
#include <string>
#include <vector>


#include "Level.h"
#include "Wall.h"
#include "GameObject.h"
#include "Player.h"
#include "Zombie.h"


Level::Level()
    : m_height{0}
    , m_width{0}
    , m_pGameObjects{ new std::vector<GameObject*>{} }
    , m_pPlayer{ nullptr }
{
}

bool Level::Load(std::string fileName)
{
    bool success{};

    std::ifstream levelFile;
    levelFile.open(fileName);
    if (levelFile)
    {
        constexpr int bufferSize{ 10 };
        char buffer[bufferSize]{ };

        levelFile.getline(buffer, bufferSize, '\n');
        m_width = std::atoi(buffer);

        levelFile.getline(buffer, bufferSize, '\n');
        m_height = std::atoi(buffer);

        if (m_width != 0 && m_height != 0)
        {
            int bufferSize = m_width + 1;
            char* pBuffer = new char[bufferSize] {};

            std::vector<char> blueprintLayer{};
            for (int i = 0; i < m_height; i++)
            {
                levelFile.getline(pBuffer, bufferSize, '\n');
                for (int c = 0; c < m_width; c++)
                {
                    blueprintLayer.push_back(*(pBuffer+c));
                }
            }

            std::vector<char> gameplayLayer{};
            for (int i = 0; i < m_height; i++)
            {
                levelFile.getline(pBuffer, bufferSize, '\n');
                for (int c = 0; c < m_width; c++)
                {
                    gameplayLayer.push_back(*(pBuffer + c));
                }
            }

            delete[] pBuffer;
            Build(blueprintLayer, gameplayLayer);
        }
    }
    levelFile.close();

    return success;
}

void Level::Build(const std::vector<char> &blueprintLayer, const std::vector<char> &gameplayLayer)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int mapIndex = MapIndexGet(x, y);
            switch (blueprintLayer[mapIndex])
            {
                case '+':
                case '-':
                case '|':
                    m_pGameObjects->push_back(new Wall{ x, y, this});
                    break;
            }

            switch (gameplayLayer[mapIndex])
            {
                case '+':
                case '-':
                case '|':
                case ' ':
                    break;

                case '@':
                    m_pPlayer = new Player{x, y, this};
                    break;

                case 'z':
                    m_pGameObjects->push_back(new Zombie{ x, y, this });
                    break;
            }
        }
    }
}

int Level::MapIndexGet(int x, int y)
{
    return (y * m_width) + x;
}

bool Level::Update(bool processInput)
{
    m_pPlayer->Update(processInput);
    for (auto pGameObject = m_pGameObjects->begin(); pGameObject != m_pGameObjects->end(); ++pGameObject)
    {
        (*pGameObject)->Update(processInput);
    }
    return false;
}

void Level::Draw()
{
    m_pPlayer->Draw();
    for (auto pGameObject = m_pGameObjects->begin(); pGameObject != m_pGameObjects->end(); ++pGameObject)
    {
        (*pGameObject)->Draw();
    }
}

GameObject* Level::GameObjectGet(int x, int y)
{
    for (auto pGameObject = m_pGameObjects->begin(); pGameObject != m_pGameObjects->end(); ++pGameObject)
    {
        if ((*pGameObject)->GetX() == x && (*pGameObject)->GetY() == y)
        {
            return (*pGameObject);
        }
    }
    return nullptr;
}
