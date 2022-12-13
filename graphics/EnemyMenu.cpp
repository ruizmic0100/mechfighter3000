#include "EnemyMenu.h"

float ImGuiWidth_Enemy = 650.0f;
float ImGuiHeight_Enemy = 450.0f;

void EnemyMenu(Player& player, Enemy& enemy)
{

    ImGui::SetNextWindowSize(ImVec2(ImGuiWidth_Enemy, ImGuiHeight_Enemy));
    ImGui::Begin("Enemy Data");
    ImGui::BeginChild("PlayerSide", ImVec2(300, 250), true);
    // ImGui::Columns(2, "FightingMenuColumns");
    // ImGui::SetColumnOffset(0, 100);
    ImGui::SetWindowFontScale(1.3);
    ImGui::Text("%s", player.playerMech.Name_.c_str());
    ImGui::SetWindowFontScale(1);
    ImGui::Dummy(ImVec2(0.0f, 5.0f));
    ImGui::Text("Lv. %u", player.playerMech.level_);

    // Mech AP bar.
    ImGui::Text("AP");
    ImGui::SameLine(40.0f);
    ImGui::Text("%u/%u", player.playerMech.currentAP_, player.playerMech.totalAP_);
    ImGui::ProgressBar(armorPointsBar, ImVec2(260.0f, 20.0f));
    ImGui::Separator();
    ImGui::Text("Head: %s", player.playerMech.head_.Name.c_str());
    ImGui::Text("Core: %s", player.playerMech.core_.Name.c_str());
    ImGui::Text("arms: %s", player.playerMech.arms_.Name.c_str());
    ImGui::Text("legs: %s", player.playerMech.legs_.Name.c_str());
    ImGui::Separator();
    ImGui::Text("Left Arm Weapon: %s", player.playerMech.leftArmWeapon_.Name.c_str());
    ImGui::Text("Right Arm Weapon: %s", player.playerMech.rightArmWeapon_.Name.c_str());
    ImGui::Text("Left Shoulder Weapon: %s", player.playerMech.leftShoulderWeapon_.Name.c_str());
    ImGui::Text("Right Shoulder Weapon: %s", player.playerMech.rightShoulderWeapon_.Name.c_str());
    ImGui::EndChild();
    // ImGui::NextColumn();
    ImGui::SameLine();
    ImGui::BeginChild("EnemySide", ImVec2(300, 250), true);
    ImGui::SetWindowFontScale(1.3);
    ImGui::Text("%s", enemy.enemyMech.Name_.c_str());
    ImGui::SetWindowFontScale(1);
    ImGui::Text("Lv. %u", enemy.enemyMech.level_);
    ImGui::Text("AP: %d", enemy.enemyMech.currentAP_);
    ImGui::Separator();
    ImGui::Text("Head: %s", enemy.enemyMech.head_.Name.c_str());
    ImGui::Text("Core: %s", enemy.enemyMech.core_.Name.c_str());
    ImGui::Text("arms: %s", enemy.enemyMech.arms_.Name.c_str());
    ImGui::Text("legs: %s", enemy.enemyMech.legs_.Name.c_str());
    ImGui::Separator();
    ImGui::Text("Left Arm Weapon: %s", enemy.enemyMech.leftArmWeapon_.Name.c_str());
    ImGui::Text("Right Arm Weapon: %s", enemy.enemyMech.rightArmWeapon_.Name.c_str());
    ImGui::Text("Left Shoulder Weapon: %s", enemy.enemyMech.leftShoulderWeapon_.Name.c_str());
    ImGui::Text("Right Shoulder Weapon: %s", enemy.enemyMech.rightShoulderWeapon_.Name.c_str());
    ImGui::EndChild();

    // Action Bar
    ImGui::BeginChild("ActionBar", ImVec2(630, 180), true);
    ImGui::Text("Actions");
    ImGui::Separator();
    // TODO: Make an action class that does all the damage calculations and error checking for these attacks.
    if(ImGui::Button("Left Arm")) {
        enemy.enemyMech.currentAP_ -= player.playerMech.leftArmWeapon_.WeaponConfigs.AttackPower_;
    }
    ImGui::SameLine(160.0f);
    if(ImGui::Button("Right Arm")) {
        enemy.enemyMech.currentAP_ -= player.playerMech.rightArmWeapon_.WeaponConfigs.AttackPower_;
    }
    if(ImGui::Button("Left Shoulder")) {
        enemy.enemyMech.currentAP_ -= player.playerMech.leftShoulderWeapon_.WeaponConfigs.AttackPower_;
    }
    ImGui::SameLine(140.0f);
    if(ImGui::Button("Right Shoulder")) {
        enemy.enemyMech.currentAP_ -= player.playerMech.rightShoulderWeapon_.WeaponConfigs.AttackPower_;
    }
    ImGui::Button("Swap Weapons");
    ImGui::SameLine(150.0f);
    ImGui::Button("Tactical Retreat");
    ImGui::EndChild();

    if (ImGui::Button("Close")) // FIXME: I can't close this window.
        Settings::Tab = 2;
    ImGui::End();
}