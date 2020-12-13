#include <iostream>

#include "GameplayStateLoading.h"
#include "GameStateGameplay.h"
#include "Level.h"


GameplayStateLoading::GameplayStateLoading(GameStateGameplay* pGameStateGameplay)
    : GameplayState{ pGameStateGameplay }
{
    m_pGameStateGameplay->GetLevel()->Load("Map/1.txt");
    pGameStateGameplay->
}

void GameplayStateLoading::Draw()
{
    system("cls");
    std::cout << "Loading..." << std::endl;
}

bool GameplayStateLoading::Update(bool processInput)
{
    return false;
}
