// #include "vld.h"
#include <iostream>
#include "LevelEditor.h";

int main()
{
    LevelEditor levelEditor;
    levelEditor.Initialize();
    levelEditor.RunGameLoop();
    levelEditor.Deinitialize();
}
