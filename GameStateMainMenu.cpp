#include <iostream>
#include "GameStateMainMenu.h"

bool GameStateMainMenu::Update(bool processInput)
{
    if (!processInput)
    {
        return true;
    }
    return true;
}

void GameStateMainMenu::Draw()
{
    system("cls");
    std::cout << "Main Menu:" << std::endl;
    std::cout << "Options" << std::endl;
    std::cout << "Play" << std::endl;
    std::cout << "Quit" << std::endl;
}
