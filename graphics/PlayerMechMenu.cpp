#include "PlayerMechMenu.h"

#include "RenderList.h"
#include "GameEventHandler.h"
#include "BattleMenu.h"

// TODO: Comment about what this does exactly.
DEFINE_ENUM(WeaponType, WEAPONTYPE)

// Defines the bounds of the inventory within the menu.
float ImGuiWidth_Inventory = 300.0f;
float ImGuiHeight_Inventory = 300.0f;

float progress=0.0f, playerAPbar=0.0f;
bool ChangeLightColor=false, isOpen=false;

// Used for the fps chart.
float avg = 0.0f;

void Render(Player& player, Enemy& enemy, unsigned int menu_textures)
{

    // Start the Dear ImGui Frame:
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    playerAPbar = player.playerMech.currentAP_;
    {
        ImGui::Begin("PlayerMechMenu");
        ImGui::Columns(2, "columns");
        ImGui::SetColumnOffset(1, 280);
        {
            // Left side:
            static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
            static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

            Theme();
            // Mech Name.
            ImGui::SetWindowFontScale(1.5);
            ImGui::Text("%s", player.playerMech.Name_.c_str());
            ImGui::SetWindowFontScale(1);
            ImGui::Image((void*)(intptr_t)menu_textures, ImVec2(32, 32));
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            // Mech Level.
            ImGui::Text("Player Lv. %u", player.playerLevel_);
            ImGui::Text("Mech Lv. %u", player.playerMech.level_);

            // Mech Exp bar.
            ImGui::Text("Exp");
            ImGui::SameLine(160.0f);
            ImGui::Text("Left: [TODO]");
            ImGui::ProgressBar(progress, ImVec2(260.0f, 20.0f));

            // Mech AP bar.
            ImGui::Text("AP");
            ImGui::SameLine(40.0f);
            ImGui::Text("%u/%u", player.playerMech.currentAP_, player.playerMech.totalAP_);
            ImGui::ProgressBar(playerAPbar, ImVec2(260.0f, 20.0f));

            // ImGui::Separator();
            // Mech Equipped Parts:
            if (player.playerMech.head_.Initialized) {
                ImGui::Text("Head: %s", player.playerMech.head_.Name.c_str());
            } else {
                ImGui::Text("Head: Nothing Equipped.");
            }
            if (player.playerMech.core_.Initialized) {
                ImGui::Text("Core: %s", player.playerMech.core_.Name.c_str());
            } else {
                ImGui::Text("Core: Nothing Equipped.");
            }
            if (player.playerMech.arms_.Initialized) {
                ImGui::Text("Arms: %s", player.playerMech.arms_.Name.c_str());
            } else {
                ImGui::Text("Arms: Nothing Equipped.");
            }
            if (player.playerMech.legs_.Initialized) {
                ImGui::Text("Legs: %s", player.playerMech.legs_.Name.c_str());
            } else {
                ImGui::Text("Legs: Nothing Equipped.");
            }
            if (player.playerMech.leftArmWeapon_.Initialized) {
                ImGui::Text("Left Arm Weapon: %s", player.playerMech.leftArmWeapon_.Name.c_str());
            } else {
                ImGui::Text("Left Arm Weapon: Nothing Equipped.");
            }
            if (player.playerMech.rightArmWeapon_.Initialized) {
                ImGui::Text("Right Arm Weapon: %s", player.playerMech.rightArmWeapon_.Name.c_str());
            } else {
                ImGui::Text("Right Arm Weapon: Nothing Equipped.");
            }
            if (player.playerMech.leftShoulderWeapon_.Initialized) {
                ImGui::Text("Left Shoulder Weapon: %s", player.playerMech.leftShoulderWeapon_.Name.c_str());
            } else {
                ImGui::Text("Left Shoulder Weapon: Nothing Equipped.");
            }
            if (player.playerMech.rightShoulderWeapon_.Initialized) {
                ImGui::Text("Right Arm Weapon: %s", player.playerMech.rightShoulderWeapon_.Name.c_str());
            } else {
                ImGui::Text("Right Arm Weapon: Nothing Equipped.");
            }

            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            
            // Make these do something.
            ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
            if (ImGui::Button("Battle", ImVec2(230 - 15, 41)))
                Settings::Tab = 1;

                ImGui::Spacing();
                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
            if (ImGui::Button("Settings", ImVec2(230 - 15, 41)))
                Settings::Tab = 2;

            ImGui::PopStyleColor(2);


            ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
            imguipp::center_text_ex("PlayerMechMenu", 230, 1, false);
        }
        /* ----------------------------------------------- Next Column -------------------------------------------------------------*/
        ImGui::NextColumn();
        {
            static float f = 0.0f;
            static int counter = 0;
            static bool animate = true;

            /* ---------------------------------- GAME INFO ---------------------------------- */
            ImGui::BeginChild("FPS", ImVec2(400, 220), true);
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

            /* ---------------------------------- GAME STATE INFO ---------------------------------- */
            std::string game_state_info_buffer;
            game_state_info_buffer = "FIXME";

            switch(GetGameState()) {
                case 0:
                    game_state_info_buffer = "GAME_START";
                    break;
                case 1:
                    game_state_info_buffer = "MAINMENU_PHASE";
                    break;
                case 2:
                    game_state_info_buffer = "BATTLE_PHASE";
                    break;
                case 3:
                    game_state_info_buffer = "LOOT_PHASE";
                    break;
                case 4:
                    game_state_info_buffer = "LOADING_PHASE";
                    break;
                case 5:
                    game_state_info_buffer = "GAME_END";
                    break;
                default:
                    std::cout << "Could not interpret gamestate.curr_state..." << std::endl;
                    break;
            }

            ImGui::Text("GAME STATE:");
            ImGui::SameLine();
            ImGui::Text("%s", game_state_info_buffer.c_str());
            /* ---------------------------------- GAME STATE INFO ---------------------------------- */

            ImGui::EndChild();
            /* ---------------------------------- GAME INFO ---------------------------------- */

            // Dumper Tab
            if (Settings::Tab == 2) {
                if (ImGui::Button("Change Light Color"))
                    ChangeLightColor = !ChangeLightColor;
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
            // TODO: Make this size dynamic.
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
                        ImGui::Text("Rarity: "); ImGui::SameLine();
                        if (player.PlayerInventory.inventoryParts_.at(i).rarity == RUST) ImGui::Text("RUST");
                        if (player.PlayerInventory.inventoryParts_.at(i).rarity == CIVILIAN) ImGui::Text("CIVILIAN");
                        if (player.PlayerInventory.inventoryParts_.at(i).rarity == MILITARY) ImGui::Text("MILITARY");
                        if (player.PlayerInventory.inventoryParts_.at(i).rarity == ALIEN) ImGui::Text("ALIEN");
                        // ImGui::Text((player.PlayerInventory.Inventory_.at(0).Parts.at(i).Notes).c_str()); // FIXME: The json file only has one giant sentence no breaks so I am going to have to make something that breaks this up into equal blocks.
                    ImGui::EndTooltip();
                }

                ImGui::SameLine(150.0f);
                // What type of part it is.
                if (player.PlayerInventory.inventoryParts_.at(i).Type == HEAD) ImGui::Text("HEAD");
                if (player.PlayerInventory.inventoryParts_.at(i).Type == CORE) ImGui::Text("CORE");
                if (player.PlayerInventory.inventoryParts_.at(i).Type == ARMS) ImGui::Text("ARMS");
                if (player.PlayerInventory.inventoryParts_.at(i).Type == LEGS) ImGui::Text("LEGS");

                ImGui::SameLine(200.0f);

                // The item ID for dev:
                ImGui::Text("%d", player.PlayerInventory.inventoryParts_.at(i).PartID);

                ImGui::Separator();
            }

            for (int i = 0; i < player.PlayerInventory.inventoryWeapons_.size(); i++) {
                sprintf(Label, "%s", player.PlayerInventory.inventoryWeapons_.at(i).Name.c_str());
                ImGui::Selectable( Label, &weaponSelection[i], ImGuiSelectableFlags_AllowDoubleClick );
                // Equip the weapon.
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                    /**
                     * @note This should fail to equip if the slot is full.
                    */
                    EquipWeapon(player.PlayerInventory.inventoryWeapons_.at(i), player);
                }

                if (ImGui::IsItemHovered()) {
                    ImGui::BeginTooltip();
                        ImGui::Text("Name: "); ImGui::SameLine(); ImGui::Text(player.PlayerInventory.inventoryWeapons_.at(i).Name.c_str());
                        ImGui::Text("Type: "); ImGui::SameLine();
                        if (player.PlayerInventory.inventoryWeapons_.at(i).WType == HANDGUN) ImGui::Text("Handgun"); // TODO: Add the rest of the types.
                        ImGui::Text("Level: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryWeapons_.at(i).weaponLevel).c_str());
                        ImGui::Text("Price: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryWeapons_.at(i).WeaponConfigs.Price_).c_str());
                        ImGui::Text("Weight: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryWeapons_.at(i).WeaponConfigs.Weight_).c_str());
                        ImGui::Text("Attack Power: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryWeapons_.at(i).WeaponConfigs.AttackPower_).c_str());
                        ImGui::Text("Energy Cost: "); ImGui::SameLine(); ImGui::Text(std::to_string(player.PlayerInventory.inventoryWeapons_.at(i).WeaponConfigs.EnergyCost_).c_str());
                        // TODO: Add the rest of the weapon configs.
                        ImGui::Text((player.PlayerInventory.inventoryWeapons_.at(i).Manufacturer).c_str());
                        ImGui::Text("Rarity: "); ImGui::SameLine();
                        if (player.PlayerInventory.inventoryWeapons_.at(i).rarity == RUST) ImGui::Text("RUST");
                        if (player.PlayerInventory.inventoryWeapons_.at(i).rarity == CIVILIAN) ImGui::Text("CIVILIAN");
                        if (player.PlayerInventory.inventoryWeapons_.at(i).rarity == MILITARY) ImGui::Text("MILITARY");
                        if (player.PlayerInventory.inventoryWeapons_.at(i).rarity == ALIEN) ImGui::Text("ALIEN");
                        // ImGui::Text((player.PlayerInventory.Inventory_.at(0).Parts.at(i).Notes).c_str()); // FIXME: The json file only has one giant sentence no breaks so I am going to have to make something that breaks this up into equal blocks.
                    ImGui::EndTooltip();
                }

                ImGui::SameLine(100.0f);
                ImGui::Text(GetString(player.PlayerInventory.inventoryWeapons_.at(i).WType));
                ImGui:: SameLine(200.0f);
                ImGui::Text(std::to_string(player.PlayerInventory.inventoryWeapons_.at(i).weaponPartID).c_str());

            }

            ImGui::EndChild();
            // INVENTORY

            if (Settings::Tab == 1) {
                if (player.playerMech.leftArmWeapon_.Equipped || player.playerMech.rightArmWeapon_.Equipped || player.playerMech.leftShoulderWeapon_.Equipped || player.playerMech.rightShoulderWeapon_.Equipped) {
                    BattlePhase();
                } else {
                    // TODO: Add popup here.
                    std::cout << "No weapon equipped" << std::endl;
                }

                Settings::Tab = 0;
            }
            if (renderBattleMenu) {
                BattleMenu::BattleMenu(player, enemy);
            }
        }
        ImGui::End();
        isOpen = true;
    }

    // Render call for ImGui.
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Theme()
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

void CustomRendering()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Primitives
    ImGui::Text("Primitives");

    static float sz = 36.0f;
    static float thickness = 4.0f;
    
}