#include "GameEventHandler.h"
#include "RenderList.h"

GameState gamestate;

enum BattleResults {
    DEFEATED = 0,
    SUCCEEDED = 1,
    TACTICAL_RETREAT = 2
};

struct BattleData {
    BattleResults outcome;
} Battle;

int GetGameState()
{
    return gamestate.curr_state;
}

void GameStart()
{
    srand((unsigned) time(NULL));
    gamestate.curr_state = GAME_START;
    std::cout << "Game Start!" << std::endl;
    Start = true; // TODO: Make start menu.

    if (Start) {
        MainMenuPhase();
    }
}

// TODO: enemy and player instances should probably be held here.
// LINK: ../graphics/renderer.cpp:146
// Enemy SpawnEnemy()
// {
//     Enemy enemyInstance;

//     return enemyInstance;
// }

void LoadingPhase()
{
    printf("LoadingPhase()\n");
    gamestate.curr_state = LOADING_PHASE;
}

void BattlePhase()
{
    printf("BattlePhase()\n");
    gamestate.curr_state = BATTLE_PHASE;
    // Enemy enemy = SpawnEnemy();
    renderBattleMenu = true;
}

void LootPhase()
{
    printf("LootPhase()\n");
    renderBattleMenu = false;
    gamestate.curr_state = LOOT_PHASE;
}

// TODO: Make this actually a main menu with game start - settings - exit game.
void MainMenuPhase()
{
    printf("MainMenuPhase()\n");
    gamestate.curr_state = MAINMENU_PHASE;
    renderer();
}

void PlayerWeaponAttack(Player& player, Enemy& enemy, unsigned int whichWeapon)
{
    // Do damage
    // Check if kills
    // Call loot phase
    switch (whichWeapon) {
        case 0: // Left arm weapon.
            enemy.enemyMech.currentAP_ -= player.playerMech.leftArmWeapon_.WeaponConfigs.AttackPower_; // TODO: Add in all the different calculations needed.
            if (enemy.enemyMech.currentAP_ <= 0) { // FIXME: Can't seem to get this to work
                enemy.enemyMech.currentAP_ = 0;
                LootPhase();
            }
            break;
        case 1: // Right arm weapon.
            enemy.enemyMech.currentAP_ -= player.playerMech.rightArmWeapon_.WeaponConfigs.AttackPower_;
            break;
        case 2: // Left shoulder weapon.
            enemy.enemyMech.currentAP_ -= player.playerMech.leftShoulderWeapon_.WeaponConfigs.AttackPower_;
            break;
        case 3: // Right shoulder weapon.
            enemy.enemyMech.currentAP_ -= player.playerMech.rightShoulderWeapon_.WeaponConfigs.AttackPower_;
            break;
        default:
            std::cout << "Could not interpret which weapon while trying to weaponattack()" << std::endl;
            break;
    }
}