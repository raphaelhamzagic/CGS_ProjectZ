// #include "vld.h"
#include "LevelEditor.h"

int main()
{
    projectz::editor::LevelEditor levelEditor;
    levelEditor.Initialize();
    levelEditor.RunGameLoop();
    levelEditor.Deinitialize();

    return 0;
}
