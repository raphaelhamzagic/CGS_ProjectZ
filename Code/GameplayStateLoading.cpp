#include <iostream>

#include "GameplayStateLoading.h"
#include "GameStateGameplay.h"
#include "Level.h"


GameplayStateLoading::GameplayStateLoading(GameStateGameplay* pGameStateGameplay)
    : GameplayState{ pGameStateGameplay }
{
    m_pGameStateGameplay->LevelGet()->Load("Map/1.txt");
    m_pGameStateGameplay->StateChange(GameStateGameplay::GameplayStateName::PLAYING);
}

void GameplayStateLoading::Draw()
{
    system("cls");
    std::cout << "Loading..." << std::endl;
}