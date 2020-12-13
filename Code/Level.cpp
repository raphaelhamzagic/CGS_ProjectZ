#include <fstream>
#include <string>
#include <vector>

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
        constexpr int bufferSize{ 100 };
        char buffer[bufferSize]{};

        levelFile.getline(buffer, bufferSize, '\n');
        m_width = std::atoi(buffer);

        levelFile.getline(buffer, bufferSize, '\n');
        m_height = std::atoi(buffer);

        if (m_width != 0 && m_height != 0)
        {
            char* pBlueprintLayer = new char[m_height * m_width]{};            
            for (int i = 0; i < m_height; i++)
            {
                levelFile.getline(buffer, bufferSize+1, '\n');
                CharCopy(buffer, pBlueprintLayer, 0, bufferSize, (bufferSize * i));
            }

            char* pGameplayLayer = new char[m_height * m_width]{};
            for (int i = 0; i < m_height; i++)
            {
                levelFile.getline(buffer, bufferSize + 1, '\n');
                CharCopy(buffer, pGameplayLayer, 0, bufferSize, (bufferSize * i));
            }

            Build(pBlueprintLayer, pGameplayLayer);
        }

        levelFile.close();
    }

    return success;
}

void Level::CharCopy(char* pOrigin, char* pDestination, int originIndex, int count, int destinationIndex)
{
    int limit = (originIndex + count) - originIndex;
    for (int i = originIndex; i < limit; i++)
    {
        pDestination[i + destinationIndex] = pOrigin[i + originIndex];
    }
}

void Level::Build(char* pBlueprintLayer, char* pGameplayLayer)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            int mapIndex = MapIndexGet(x, y);
            switch (pBlueprintLayer[mapIndex])
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