#include <iostream>
#include <fstream>
#include "Level.h"
#include "Point.h"

using namespace std;

Level::~Level()
{
    if (m_pBlueprint)
    {
        delete[] m_pBlueprint;
        m_pBlueprint = nullptr;
    }
    if (m_pElements)
    {
        delete[] m_pElements;
        m_pElements = nullptr;
    }
}

int Level::GetLevelHeight()
{
    return m_height;
}

int Level::GetLevelWidth()
{
    return m_width;
}

void Level::SetLevelDimensions()
{
    cout << "Enter the width of your level: ";
    cin >> m_width;

    cout << "Enter the height of your level: ";
    cin >> m_height;
}

void Level::NewLevel()
{
    SetLevelDimensions();
    m_pBlueprint = new char[m_width * m_height];
    m_pElements = new char[m_width * m_height];
    for (int i = 0; i < m_width * m_height; i++)
    {
        m_pBlueprint[i] = ' ';
        m_pElements[i] = ' ';
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

        m_pBlueprint = new char[m_width * m_height];
        m_pElements = new char[m_width * m_height];

        std::streamsize levelSize = static_cast<std::streamsize>(m_width) * static_cast<std::streamsize>(m_height);
        levelFile.read(m_pBlueprint, levelSize);
        levelFile.read(m_pElements, levelSize);

        levelFile.close();
    }

    return true;
}

bool Level::SaveLevel()
{
    if (m_fileName.empty())
    {
        cout << "Pick a name for your level file (eg: Level1.txt): ";
        cin >> m_fileName;
        m_fileName.insert(0, "../Maps/");
    }   

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
        levelFile.write(m_pBlueprint, (long long)m_width * (long long)m_height);
        // TODO
        if (!levelFile)
        {
            cout << "Write failed!" << endl;
        }
        levelFile.close();
    }
    return true;
}

int Level::GetIndexFromXY(int x, int y)
{
    return x + y * m_width;
}

void Level::DrawLevelBlueprint(Point* pCursor)
{
    //DisplayTopBorder(width);

    for (int y = 0; y < m_height; y++)
    {
       // DisplayLeftBorder();
        for (int x = 0; x < m_width; x++)
        {
            if (pCursor->x == x && pCursor->y == y)
            {
                cout << kCursor;
            }
            else
            {
                int index = GetIndexFromXY(x, y);
                cout << m_pBlueprint[index];
            }
        }
        //DisplayRightBorder();
        cout << endl;
    }

    //DisplayBottomBorder(width);
}

void Level::SetLevelBlueprintCharacter(Point* pPosition, char character)
{
    int index = GetIndexFromXY(pPosition->x, pPosition->y);
    m_pBlueprint[index] = character;
}



/*
* 
* // Borders: ASCII code for the borders (https://theasciicode.com.ar/)
constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;


void DisplayTopBorder(int width)
{
    cout << kTopLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}
void DisplayBottomBorder(int width)
{
    cout << kBottomLeftBorder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;
}
void DisplayLeftBorder()
{
    cout << kVerticalBorder;
}
void DisplayRightBorder()
{
    cout << kVerticalBorder << endl;
}

*/