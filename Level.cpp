#include <fstream>
#include <iostream>
#include <string>

#include "Level.h"


Level::Level()
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
        m_width = atoi(buffer);

        levelFile.getline(buffer, bufferSize, '\n');
        m_height = atoi(buffer);

        if (m_width != 0 && m_height != 0)
        {
            char* pBlueprintLayer = new char[m_height * m_width];
            levelFile.getline(pBlueprintLayer, bufferSize + 1, '\n');

            char* pGameplayLayer = new char[m_height * m_width];
            levelFile.getline(pGameplayLayer, bufferSize + 1, '\n');
        }

        levelFile.close();
    }

    return success;
}

void Level::Convert(char* pBlueprintLayer, char* pGameplayLayer)
{

}


