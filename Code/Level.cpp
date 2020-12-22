#include <fstream>
// #include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Level.h"
#include "Wall.h"
#include "GameObject.h"


Level::Level()
    : m_height{0}
    , m_width{0}
    , m_pGameObjects{ new std::vector<GameObject*>{} }
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

bool Level::Update(bool processInput)
{
    if (processInput)
    {
        ProcessInput();
    }
    return false;
}

void Level::ProcessInput()
{
    int input = _getch();
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
                    m_pGameObjects->push_back(new Wall{ x, y});
                    break;
            }
        }
    }
}

int Level::MapIndexGet(int x, int y)
{
    return (y * m_width) + x;
}

void Level::Draw()
{
    for (auto pGameObject = m_pGameObjects->begin(); pGameObject != m_pGameObjects->end(); ++pGameObject)
    {
        (*pGameObject)->Draw();
    }
}