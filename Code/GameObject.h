#pragma once

class Level;

class GameObject
{
public:
    enum class GameObjectType
    {
        WALL,
        DOOR,
        ZOMBIE,
        KEY,
        AMMO,
        PLAYER
    };
    enum class GameObjectColor
    {
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15,
        SolidGreen = 34,
        SolidRed = 68,
        SolidBlue = 153,
        Default = 7
    };

    GameObject(int x, int y, char mainSymbol, GameObjectType type, Level* pLevel, GameObjectColor color = GameObjectColor::LightGray);
    virtual void Draw();
    virtual void Update(bool processInput);
    int GetX();
    int GetY();

protected:
    GameObjectType m_type;
    GameObjectColor m_color;
    bool m_active;
    int m_x;
    int m_y;
    char m_symbol;
    Level* m_pLevel;
};

