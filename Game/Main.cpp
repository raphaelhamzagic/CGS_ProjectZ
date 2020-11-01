// #include "vld.h"
#include <iostream>
#include "Game.h"
#include "AudioManager.h"
#include "StateMachineExampleGame.h"


using namespace std;

int main()
{
    projectz::game::Game myGame;
    projectz::game::StateMachineExampleGame gameStateMachine(&myGame);

    myGame.Initialize(&gameStateMachine);
    myGame.RunGameLoop();
    myGame.Deinitialize();
    
    projectz::game::AudioManager::GetInstance()->DestroyInstance();
    return 0;
}