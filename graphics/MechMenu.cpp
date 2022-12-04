#include "MechMenu.h"

float ImGuiWidth_Inventory = 300.f;
float ImGuiHeight_Inventory = 300.f;

float ImGuiWidth_Enemy = 500.0f;
float ImGuiHeight_Enemy = 500.0f;

static float progress = 0.0f;
static float armorPointsBar = 0.0f;
    
float avg = 0.0f;

void MechMenu::Render()
{
    ImGui::Columns(2);
    ImGui::SetColumnOffset(1, 230);

    {
        // Left side:
        static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
        static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

        ImGui::Begin("NewMechMenu");
        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);;
        if (ImGui::Button("Button One", ImVec2(230 - 15, 41)))
            Settings::Tab = 1;

            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
        if (ImGui::Button("Button Two", ImVec2(230 - 15, 41)))
            Settings::Tab = 2;

        ImGui::PopStyleColor(2);

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
        imguipp::center_text_ex("NewMechMenu", 230, 1, false);
        ImGui::End();
    }

    ImGui::NextColumn();

    // Right side
    {
        // Dumper Tab
        if (Settings::Tab == 2) {
            static ImGuiTextFilter filter;
            static std::vector<std::string> resources = {
                "_cfx_internal"
            };

            filter.Draw(" Search", 240);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
            if (ImGui::ListBoxHeader("##ResourcesList", ImVec2(imguipp::getx(), imguipp::gety() - 35))) {
                for (const auto& resource : resources) {
                    if (filter.PassFilter(resource.c_str())) {
                        if (ImGui::TreeNode(resource.c_str()))
                            ImGui::TreePop();
                    }
                }
                ImGui::ListBoxFooter();
            }
            ImGui::PopStyleColor();
            if (ImGui::Button(" Save to folder", ImVec2(205, 32))) {}
        }
    }
}

void MechMenu::Theme()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowBorderSize = 0;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->WindowMinSize = ImVec2(300, 330);

    style->FramePadding = ImVec2(8, 6);

    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

    style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

    style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
    style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

    style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

    style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
}

void RenderMechMenu(Player& player, Enemy& enemy) {
    armorPointsBar = player.playerMech.currentAP_;

    // Start the Dear ImGui Frame:
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Show a simple window for the player's Mech Menu. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;
        static bool animate = true;

        // Start of Mech Data Window.
        ImGui::Begin("Mech Data");
        MechMenu::Theme();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Animate", &animate);

        // TODO: Fix the avg label.
        // Show fps data as a graph.
        static float values[90] = { 0 };
        static int values_offset = 0;
        char avgLabel[40];
        if (animate)
        {
            static float refresh_time = ImGui::GetTime(); // Create dummy data at fixed 60 hz rate for the demo
            for (; ImGui::GetTime() > refresh_time + 1.0f/30.0f; refresh_time += 1.0f/30.0f)
            {
                static float phase = 0.0f;
                values[values_offset] = cosf(phase) + ImGui::GetIO().Framerate;
                values_offset = (values_offset+1) % IM_ARRAYSIZE(values);
                phase += 0.10f*values_offset;
                avg += values[values_offset];
                avg = (avg / 11);
                if (values_offset % 10 == 0)
                    avg = values[values_offset];
            }
        }
        sprintf(avgLabel, "Avg: %.1f", avg);
        ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, avgLabel, -1.0f, 1.0f, ImVec2(100,80));
        ImGui::Separator();

        if (ImGui::Button("New Mech Menu"))
            showNewMechMenu = !showNewMechMenu;

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

        // Armor Parts Portion.
        for (int i = 0; i < player.PlayerInventory.Inventory_.at(0).Parts.size(); i++) {
            // Name of Item and making it clickable:
            sprintf(Label, "%s", player.PlayerInventory.Inventory_.at(0).Parts.at(i).Name.c_str());
            ImGui::Selectable( Label, &selection[i], ImGuiSelectableFlags_AllowDoubleClick );

            // Equip the part if double clicked.
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                if (player.playerMech.checkIfSlotIsFull(HEAD)) { // FIXME: Fix this.
                    ImGui::OpenPopup("HeadSlotFull");
                    if(ImGui::BeginPopup("HeadSlotFull")) {
                        ImGui::Text("Head Slot Full!");
                    }
                    ImGui::EndPopup();
                }

                /**
                 * @note This should fail to equip if the slot is full.
                */
                EquipPart(player.PlayerInventory.Inventory_.at(0).Parts.at(i), player);
            }


            // Show a small label tooltip.
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Part name.");

            ImGui::SameLine(150.0f);
            // What type of part:
            if (player.PlayerInventory.Inventory_.at(0).Parts.at(i).Type == HEAD) ImGui::Text("HEAD");
            if (player.PlayerInventory.Inventory_.at(0).Parts.at(i).Type == CORE) ImGui::Text("CORE");
            if (player.PlayerInventory.Inventory_.at(0).Parts.at(i).Type == ARMS) ImGui::Text("ARMS");
            if (player.PlayerInventory.Inventory_.at(0).Parts.at(i).Type == LEGS) ImGui::Text("LEGS");

            // Show a small label tooltip.
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Type of part.");

            ImGui::SameLine(200.0f);

            // The item ID for dev:
            ImGui::Text("%d", player.PlayerInventory.Inventory_.at(0).Parts.at(i).PartID);

            // Show a small label tooltip.
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Part ID.");
            ImGui::Separator();
        }

        for (int i = 0; i < player.PlayerInventory.Inventory_.at(0).Weapons.size(); i++) {
            sprintf(Label, "%s", player.PlayerInventory.Inventory_.at(0).Weapons.at(i).Name.c_str());
            ImGui::Selectable( Label, &selection[i], ImGuiSelectableFlags_AllowDoubleClick );
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

    if (showNewMechMenu) {
        MechMenu::Render();
    }

    // Render call for ImGui.
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}