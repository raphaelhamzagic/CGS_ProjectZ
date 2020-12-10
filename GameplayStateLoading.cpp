#include <iostream>

#include "GameplayStateLoading.h"
#include "GameStateGameplay.h"


GameplayStateLoading::GameplayStateLoading(GameStateGameplay* pGameStateGameplay)
    : GameplayState{ pGameStateGameplay }
{
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
