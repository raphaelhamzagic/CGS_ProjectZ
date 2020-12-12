#include <iostream>
#include "GameStateMainMenu.h"
#include "GameStateMachine.h"

GameStateMainMenu::GameStateMainMenu(GameStateMachine* pGameStateMachine)
    : GameState{ pGameStateMachine }
{
}

bool GameStateMainMenu::Update(bool processInput)
{
    if (processInput)
    {
        return ProcessInput();
    }
    else
    {
        return true;
    }    
}

bool GameStateMainMenu::ProcessInput()
{
    bool leaveGameLoop = false;

    m_isInvalidInput = false;
    int inputOption{};
    std::cin >> inputOption;

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        m_isInvalidInput = true;
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (inputOption)
        {
            case static_cast<int>(MenuOption::OPTIONS) :
                m_pGameStateMachine->ChangeState(GameStateMachine::GameStateName::OPTIONS);
                break;

            case static_cast<int>(MenuOption::PLAY) :
                m_pGameStateMachine->ChangeState(GameStateMachine::GameStateName::GAMEPLAY);
                break;

            case static_cast<int>(MenuOption::EXIT) :
                leaveGameLoop = true;
                break;

            default:
                m_isInvalidInput = true;
        }
    }

    return leaveGameLoop;
}
  


void GameStateMainMenu::Draw()
{
    system("cls");
    std::cout << "MAIN MENU" << std::endl;
    std::cout << "=========" << std::endl << std::endl;

    std::cout << static_cast<int>(MenuOption::PLAY) << ": Play" << std::endl;
    std::cout << static_cast<int>(MenuOption::OPTIONS) << ": Options" << std::endl;
    std::cout << static_cast<int>(MenuOption::EXIT) << ": Exit" << std::endl;
    std::cout << std::endl<< "Select an option: ";
    if (m_isInvalidInput)
    {
        std::cout << std::endl << "Invalid option! Select an option: " << std::endl;
    }
}
