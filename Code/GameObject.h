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
        AMMO
    };

    GameObject(int x, int y);
    virtual void Draw();
    virtual void Update(bool processInput, Level* pLevel);

private:
    GameObjectType m_type;
    int m_x;
    int m_y;
};

