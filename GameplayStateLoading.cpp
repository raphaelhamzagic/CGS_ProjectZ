#include <iostream>

#include "GameplayStateLoading.h"
#include "GameStateGameplay.h"
#include "Level.h"


GameplayStateLoading::GameplayStateLoading(GameStateGameplay* pGameStateGameplay)
    : GameplayState{ pGameStateGameplay }
{
    Level* pLevel = m_pGameStateGameplay->GetLevel();
    pLevel->Load("../Map/1.txt");
}

void GameplayStateLoading::Draw()
{
    system("cls");
    std::cout << "Loading..." << std::endl;
}

bool GameplayStateLoading::Update(bool processInput)
{
    system("pause");
    return false;
}
