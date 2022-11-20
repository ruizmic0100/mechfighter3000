#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <GLFW/glfw3.h>

#include "../graphics/Renderer.h"
#include "../util/logging.h"
#include "GameEventHandler.h"


int main(void)
{
    OutputDebugStringW(L"Test\n");
    GameStart();

}
