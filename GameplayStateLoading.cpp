#include <iostream>

#include "GameplayStateLoading.h"
#include "GameplayStateMachine.h"


GameplayStateLoading::GameplayStateLoading(GameplayStateMachine* pGameplayStateMachine)
    : GameplayState{ pGameplayStateMachine }
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
