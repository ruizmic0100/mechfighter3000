#include "MechMenu.h"

float ImGuiWidth_Inventory = 300.f;
float ImGuiHeight_Inventory = 300.f;

float ImGuiWidth_Enemy = 500.0f;
float ImGuiHeight_Enemy = 500.0f;

static float progress = 0.0f;
static float armorPointsBar = 0.0f;

void MechMenu(Player& player, Enemy& enemy) {
    armorPointsBar = player.playerMech.currentAP_;

    // Start the Dear ImGui Frame:
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show a simple window for the player's Mech Menu. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        // Start of Mech Data Window.
        ImGui::Begin("Mech Data");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Separator();

        // Mech Name.
        ImGui::Text("%s", player.playerMech.Name_.c_str());

        // Mech Level.
        ImGui::Text("Lv. %u", player.playerMech.level_);

        // Mech Exp bar.
        ImGui::Text("Exp");
        ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));

        // Mech AP bar.
        ImGui::Text("AP");
        ImGui::SameLine(40.0f);
        ImGui::Text("%u/%u", player.playerMech.currentAP_, player.playerMech.totalAP_);

        ImGui::ProgressBar(armorPointsBar, ImVec2(0.0f, 0.0f));
        
        ImGui::Separator();

        // Mech Equipped Parts:
        ImGui::Text("Equipped Parts");
        if (!player.playerMech.head_.Name.empty()) {
            ImGui::Text("Head: %s", player.playerMech.head_.Name.c_str());
        } else {
            ImGui::Text("Head: Nothing Equipped.");
        }
        if (!player.playerMech.core_.Name.empty()) {
            ImGui::Text("Core: %s", player.playerMech.core_.Name.c_str());
        } else {
            ImGui::Text("Core: Nothing Equipped.");
        }
        if (!player.playerMech.arms_.Name.empty()) {
            ImGui::Text("Arms: %s", player.playerMech.arms_.Name.c_str());
        } else {
            ImGui::Text("Arms: Nothing Equipped.");
        }
        if (!player.playerMech.legs_.Name.empty()) {
            ImGui::Text("Legs: %s", player.playerMech.legs_.Name.c_str());
        } else {
            ImGui::Text("Legs: Nothing Equipped.");
        }
        
        if (ImGui::Button("Inventory"))
            showInventory = !showInventory;

        if (ImGui::Button("Fight"))
            showEnemyWindow = !showEnemyWindow;
            
        ImGui::End();
    }

    isOpen = true;

    if (showInventory) {
        static bool selection[5] = { false, false, false, false, false };
        char Label[50];
        ImGui::SetNextWindowSize(ImVec2(ImGuiWidth_Inventory, ImGuiHeight_Inventory));
        ImGui::Begin("Inventory", &showInventory); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool)
        for (int i = 0; i < player.PlayerInventory.inventorySlots_; i++) {
            // Name of Item and making it clickable:
            sprintf(Label, "%s", player.PlayerInventory.Inventory_.at(i).Name.c_str());
            ImGui::Selectable( Label, &selection[i], ImGuiSelectableFlags_AllowDoubleClick );

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                EquipPart(player.PlayerInventory.Inventory_.at(i), player);
            }

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Part name.");

            ImGui::SameLine(150.0f);
            // What type of part:
            if (player.PlayerInventory.Inventory_.at(i).Type == HEAD) ImGui::Text("HEAD");
            if (player.PlayerInventory.Inventory_.at(i).Type == CORE) ImGui::Text("CORE");
            if (player.PlayerInventory.Inventory_.at(i).Type == ARMS) ImGui::Text("ARMS");
            if (player.PlayerInventory.Inventory_.at(i).Type == LEGS) ImGui::Text("LEGS");

            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Type of part.");
            ImGui::SameLine(200.0f);
            // The item ID for dev:
            ImGui::Text("%d", player.PlayerInventory.Inventory_.at(i).PartID);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Part ID.");
            ImGui::Separator();
        }

        ImGui::End();
    }

    if (showEnemyWindow)
    {
        ImGui::SetNextWindowSize(ImVec2(ImGuiWidth_Enemy, ImGuiHeight_Enemy));
        ImGui::Begin("Enemy Data");
        ImGui::Text("%s", enemy.enemyMech.Name_.c_str());
        ImGui::Text("%d", enemy.enemyMech.level_);
        if (ImGui::Button("Close"))
            showEnemyWindow = false;
        ImGui::End();
    }

    // Render call for ImGui.
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}