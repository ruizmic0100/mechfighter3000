#include "PopUpMenu.h"

void PopUpMenu(std::string Message)
{
    ImGui::OpenPopup(Message.c_str());
}