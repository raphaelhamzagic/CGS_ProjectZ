#pragma once

class GameStateMachine;

class Game
{
    GameStateMachine* m_stateMachine;

public:
    Game();
    void Loop();
    ~Game();
};
