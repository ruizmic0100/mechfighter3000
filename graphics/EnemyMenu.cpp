#include "EnemyMenu.h"

float ImGuiWidth_Enemy = 500.0f;
float ImGuiHeight_Enemy = 500.0f;

void EnemyMenu()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show a simple window for the enemy Mech.
    {
        ImGui::Begin("Enemy Data");

        ImGui::Text("Enemy Mech");
        ImGui::Text("AP: %d");

        ImGui::End();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}