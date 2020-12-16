#include "GameplayStatePlaying.h"
#include "GameStateGameplay.h"
#include "Level.h"

GameplayStatePlaying::GameplayStatePlaying(GameStateGameplay* pGameStateGameplay)
    : GameplayState{ pGameStateGameplay }
{
}

bool GameplayStatePlaying::Update(bool processInput)
{
    return false;
}

void GameplayStatePlaying::Draw()
{
    m_pGameStateGameplay->LevelGet()->Draw();
    system("pause");
}
