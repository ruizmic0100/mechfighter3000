#include "MechMenu.h"

DEFINE_ENUM(WeaponType, WEAPONTYPE)

float ImGuiWidth_Inventory = 300.f;
float ImGuiHeight_Inventory = 300.f;

float ImGuiWidth_Enemy = 500.0f;
float ImGuiHeight_Enemy = 500.0f;

static float progress = 0.0f;
static float armorPointsBar = 0.0f;
    
float avg = 0.0f;

void MechMenu::Render(Player& player, Enemy& enemy)
{
    // Start the Dear ImGui Frame:
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    armorPointsBar = player.playerMech.currentAP_;



    {
        ImGui::Begin("MechMenu");
        ImGui::Columns(2, "columns");
        ImGui::SetColumnOffset(1, 280);
        {
            // Left side:
            static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
            static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

            MechMenu::Theme();
            // Mech Name.
            ImGui::SetWindowFontScale(1.5);
            ImGui::Text("%s", player.playerMech.Name_.c_str());
            ImGui::SetWindowFontScale(1);
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            // Mech Level.
            ImGui::Text("Lv. %u", player.playerMech.level_);

            // Mech Exp bar.
            ImGui::Text("Exp");
            ImGui::SameLine(160.0f);
            ImGui::Text("Left: [TODO]");
            ImGui::ProgressBar(progress, ImVec2(260.0f, 20.0f));

            // Mech AP bar.
            ImGui::Text("AP");
            ImGui::SameLine(40.0f);
            ImGui::Text("%u/%u", player.playerMech.currentAP_, player.playerMech.totalAP_);
            ImGui::ProgressBar(armorPointsBar, ImVec2(260.0f, 20.0f));

            // ImGui::Separator();
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
            if (!player.playerMech.leftArmWeapon_.Name.empty()) {
                ImGui::Text("Left Arm: Nothing Equipped.");
            } else {
                ImGui::Text("Left Arm: %s", player.playerMech.leftArmWeapon_.Name.c_str());
            }
            if (!player.playerMech.rightArmWeapon_.Name.empty()) {
                ImGui::Text("Right Arm: Nothing Equipped.");
            } else {
                ImGui::Text("Right Arm: %s", player.playerMech.rightArmWeapon_.Name.c_str());
            }
            if (!player.playerMech.leftShoulderWeapon_.Name.empty()) {
                ImGui::Text("Left Shoulder: Nothing Equipped.");
            } else {
                ImGui::Text("Left Shoulder: %s", player.playerMech.leftShoulderWeapon_.Name.c_str());
            }
            if (!player.playerMech.rightShoulderWeapon_.Name.empty()) {
                ImGui::Text("Right Arm: Nothing Equipped.");
            } else {
                ImGui::Text("Right Arm: %s", player.playerMech.rightShoulderWeapon_.Name.c_str());
            }

            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            
            // Make these do something.
            ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
            if (ImGui::Button("Button One", ImVec2(230 - 15, 41)))
                Settings::Tab = 1;

                ImGui::Spacing();
                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
            if (ImGui::Button("Button Two", ImVec2(230 - 15, 41)))
                Settings::Tab = 2;

            ImGui::PopStyleColor(2);


            ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
            imguipp::center_text_ex("MechMenu", 230, 1, false);
        }
        /* ----------------------------------------------- Next Column -------------------------------------------------------------*/
        ImGui::NextColumn();
        // Right side
        {
            static float f = 0.0f;
            static int counter = 0;
            static bool animate = true;

            // FPS GRAPH
            ImGui::BeginChild("FPS", ImVec2(400, 180), true);
            ImGui::SetWindowFontScale(1.5);
            ImGui::Text("FPS");
            ImGui::SetWindowFontScale(1);
            ImGui::Dummy(ImVec2(0.0f, 5.0f));
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
            ImGui::EndChild();
            // FPS GRAPH

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
            // Dumper Tab

            // INVENTORY
            static bool partSelection[5] = { false, false, false, false, false };
            static bool weaponSelection[5] = { false, false, false, false, false };
            char Label[50];
            ImGui::BeginChild("Inventory", ImVec2(400,300), true);
            ImGui::SetWindowFontScale(1.5);
            ImGui::Text("Inventory");
            ImGui::SetWindowFontScale(1);
            ImGui::Dummy(ImVec2(0.0f,5.0f));
            ImGui::SetNextWindowSize(ImVec2(ImGuiWidth_Inventory, ImGuiHeight_Inventory));

            // Armor Parts Portion.
            for (int i = 0; i < player.PlayerInventory.inventoryParts_.size(); i++) {
                // Name of Item and making it clickable:
                sprintf(Label, "%s", player.PlayerInventory.inventoryParts_.at(i).Name.c_str());
                ImGui::Selectable( Label, &partSelection[i], ImGuiSelectableFlags_AllowDoubleClick );

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
                    EquipPart(player.PlayerInventory.inventoryParts_.at(i), player);
                }


                // Show a small label tooltip.
                if (ImGui::IsItemHovered()) {
                    ImGui::BeginTooltip();
                        ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text(player.PlayerInventory.inventoryParts_.at(i).Name.c_str());
                        ImGui::Text("Type: "); ImGui::SameLine();
                        if (player.PlayerInventory.inventoryParts_.at(i).Type == HEAD) ImGui::Text("HEAD");
                        if (player.PlayerInventory.inventoryParts_.at(i).Type == CORE) ImGui::Text("CORE");
                        if (player.PlayerInventory.inventoryParts_.at(i).Type == ARMS) ImGui::Text("ARMS");
                        if (player.PlayerInventory.inventoryParts_.at(i).Type == LEGS) ImGui::Text("LEGS");
                        ImGui::Text("Weight: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryParts_.at(i).Weight).c_str());
                        ImGui::Text("Price: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryParts_.at(i).Price).c_str());
                        ImGui::Text("Ballistic Defense: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryParts_.at(i).BallisticDefense).c_str());
                        ImGui::Text("Energy Defense: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryParts_.at(i).EnergyDefense).c_str());
                        ImGui::Text("Armor Points: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryParts_.at(i).ArmorPoints).c_str());
                        ImGui::Text((player.PlayerInventory.inventoryParts_.at(i).Manufacturer).c_str());
                        // ImGui::Text((player.PlayerInventory.Inventory_.at(0).Parts.at(i).Notes).c_str()); // FIXME: The json file only has one giant sentence no breaks so I am going to have to make something that breaks this up into equal blocks.
                    ImGui::EndTooltip();
                }

                ImGui::SameLine(150.0f);
                // What type of part is equipped on the player:
                if (player.PlayerInventory.inventoryParts_.at(i).Type == HEAD) ImGui::Text("HEAD");
                if (player.PlayerInventory.inventoryParts_.at(i).Type == CORE) ImGui::Text("CORE");
                if (player.PlayerInventory.inventoryParts_.at(i).Type == ARMS) ImGui::Text("ARMS");
                if (player.PlayerInventory.inventoryParts_.at(i).Type == LEGS) ImGui::Text("LEGS");

                ImGui::SameLine(200.0f);

                // The item ID for dev:
                ImGui::Text("%d", player.PlayerInventory.inventoryParts_.at(i).PartID);

                ImGui::Separator();
            }

            // NOTE: This second forloop necessary?
            for (int i = 0; i < player.PlayerInventory.inventoryWeapons_.size(); i++) {
                sprintf(Label, "%s", player.PlayerInventory.inventoryWeapons_.at(i).Name.c_str());
                ImGui::Selectable( Label, &weaponSelection[i], ImGuiSelectableFlags_AllowDoubleClick );

                ImGui::SameLine(200.0f);

                ImGui::Text(GetString(player.PlayerInventory.inventoryWeapons_.at(i).WType));
            }
            ImGui::EndChild();
            // INVENTORY

            if (showEnemyWindow) {
                ImGui::SetNextWindowSize(ImVec2(ImGuiWidth_Enemy, ImGuiHeight_Enemy));
                ImGui::Begin("Enemy Data");
                ImGui::Text("%s", enemy.enemyMech.Name_.c_str());
                ImGui::Text("%d", enemy.enemyMech.level_);
                if (ImGui::Button("Close"))
                    showEnemyWindow = false;
                ImGui::End();
            }
        }
        ImGui::End();
        isOpen = true;
    }

    // Render call for ImGui.
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MechMenu::Theme()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowBorderSize = 0;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->WindowMinSize = ImVec2(300, 330);

    style->FramePadding = ImVec2(8, 6);

    style->Colors[ImGuiCol_TitleBg] = ImColor(134, 170, 227, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(134, 170, 227, 255);
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

void MechMenu::CustomRendering()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Primitives
    ImGui::Text("Primitives");

    static float sz = 36.0f;
    static float thickness = 4.0f;
    
}