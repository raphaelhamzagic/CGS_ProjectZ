// #include "vld.h"
#include "LevelEditor.h"

int main()
{
    LevelEditor levelEditor;
    levelEditor.Initialize();
    levelEditor.RunGameLoop();
    levelEditor.Deinitialize();

    return 0;
}
