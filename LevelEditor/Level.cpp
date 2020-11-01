#include <iostream>
#include <fstream>
#include "Level.h"
#include "Point.h"

using namespace std;

Level::~Level()
{
    if (m_pLevelBlueprint)
    {
        delete[] m_pLevelBlueprint;
        m_pLevelBlueprint = nullptr;
    }
    if (m_pLevelGameplay)
    {
        delete[] m_pLevelGameplay;
        m_pLevelGameplay = nullptr;
    }
}

string Level::GetLevelFilename()
{
    return m_fileName;
}

int Level::GetLevelHeight()
{
    return m_height;
}

int Level::GetLevelWidth()
{
    return m_width;
}

char* Level::GetLevelBlueprint()
{
    return m_pLevelBlueprint;
}

char* Level::GetLevelGameplay()
{
    return m_pLevelGameplay;
}

int Level::GetIndexFromXY(int x, int y)
{
    return x + y * m_width;
}

void Level::NewLevel()
{
    cout << "Pick a name for your level file (eg: Level1.txt): ";
    cin >> m_fileName;
    m_fileName.insert(0, "../Maps/");

    m_width = kLevelWidth;
    m_height = klevelHeight;

    m_pLevelBlueprint = new char[m_width * m_height];
    m_pLevelGameplay = new char[m_width * m_height];
    for (int i = 0; i < m_width * m_height; i++)
    {
        m_pLevelBlueprint[i] = ' ';
        m_pLevelGameplay[i] = ' ';
    }
}

bool Level::LoadLevel()
{
    cout << "Enter Level name: ";
    cin >> m_fileName;

    m_fileName.insert(0, "../Maps/");

    ifstream levelFile;
    levelFile.open(m_fileName);
    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
        return false;
    }
    else
    {
        constexpr int tempSize = 25;
        char temp[tempSize];

        levelFile.getline(temp, tempSize, '\n');
        m_width = atoi(temp);

        levelFile.getline(temp, tempSize, '\n');
        m_height = atoi(temp);

        m_pLevelBlueprint = new char[m_width * m_height];
        m_pLevelGameplay = new char[m_width * m_height];
        const int levelSize = m_width * m_height;

        /*
        std::streamsize levelSize = static_cast<std::streamsize>(m_width) * static_cast<std::streamsize>(m_height);
        levelFile.read(m_pLevelBlueprint, levelSize+1);
        levelFile.read(m_pLevelGameplay, levelSize);
        */
        levelFile.getline(m_pLevelBlueprint, levelSize, '\n');
        levelFile.getline(m_pLevelGameplay, levelSize, '\n');

        levelFile.close();
    }

    return true;
}

bool Level::SaveLevel()
{
    ofstream levelFile;
    levelFile.open(m_fileName);
    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
        return false;
    }
    else
    {
        levelFile << m_width << endl;
        levelFile << m_height << endl;
        std::streamsize levelSize = static_cast<std::streamsize>(m_width) * static_cast<std::streamsize>(m_height);
        levelFile.write(m_pLevelBlueprint, levelSize);
        levelFile << endl;
        levelFile.write(m_pLevelGameplay, levelSize);
        if (!levelFile)
        {
            cout << "Write failed!" << endl;
        }
        levelFile.close();
    }
    return true;
}