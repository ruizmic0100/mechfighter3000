#include "MechMenu.h"


void MechMenu(Player* player) {

    // Setup Dear ImGui Style:
    // ImGui::StyleColorsDark();

    // Start the Dear ImGui Frame:
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show a simple window. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Mech Data"); // Create a window called "Hello, World" and append into it.
        
        ImGui::Text("Dev Mech"); // Display some text (you can use a format strings too).
        ImGui::Checkbox("Mech Data Window", &isOpen); // Edit bools storing our window open/close state.
        ImGui::Checkbox("Inventory", &showInventory);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f.

        if (ImGui::Button("Increase Stat"))        // Buttons return true when clicked (most widgets return true when editted/activated).
            counter++;
        
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Name: %s", player->equippedFrame->Name_.c_str());
        ImGui::Text("Manufacturer: %s", player->equippedFrame->Manufacturer_.c_str());
        ImGui::Text("Identifier: %s", player->equippedFrame->Identifier_.c_str());
        ImGui::Text("Price: %d", player->equippedFrame->Price_);
        ImGui::Text("Name: %d", player->equippedFrame->Weight_);
        ImGui::Text("Ballistic Defense: %i", player->equippedFrame->Defenses_.ballisticDefense);
        ImGui::Text("Energy Defense: %i", player->equippedFrame->Defenses_.energyDefense);
        ImGui::End();
    }

    isOpen = true;

    if (showInventory) {
        ImGui::Begin("Inventory", &showInventory); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool)
        ImGui::Text("Inventory");
        if (ImGui::Button("Close Inventory"))
            showInventory = false;
        ImGui::End();
    }

    // Render call for ImGui.
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}