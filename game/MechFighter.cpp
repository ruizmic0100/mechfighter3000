#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <GLFW/glfw3.h>

#include "../graphics/renderer.h"
#include "../util/logging.h"





int main(void)
{
    OutputDebugStringW(L"Test\n");
   
    renderer(); // Initializes the renderer.

}
