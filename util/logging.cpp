#if _WIN32
#include <windows.h>
#endif

#include <iostream>

#include "logging.h"

void Log(std::string message)
{
    std::cout << message << std::endl;
}