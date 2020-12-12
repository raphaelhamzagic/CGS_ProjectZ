#include <fstream>
#include <string>

#include "Level.h"


Level::Level()
    : m_height{0}
    , m_width{0}
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
                CopyChars(buffer, pBlueprintLayer, 0, bufferSize, (bufferSize * i));
            }

            char* pGameplayLayer = new char[m_height * m_width]{};
            for (int i = 0; i < m_height; i++)
            {
                levelFile.getline(buffer, bufferSize + 1, '\n');
                CopyChars(buffer, pGameplayLayer, 0, bufferSize, (bufferSize * i));
            }
        }

        levelFile.close();
    }

    return success;
}

void Level::CopyChars(char* pOrigin, char* pDestination, int originIndex, int count, int destinationIndex)
{
    int limit = (originIndex + count) - originIndex;
    for (int i = originIndex; i < limit; i++)
    {
        pDestination[i + destinationIndex] = pOrigin[i + originIndex];
    }
}

void Level::Build(char* pBlueprintLayer, char* pGameplayLayer)
{

}
