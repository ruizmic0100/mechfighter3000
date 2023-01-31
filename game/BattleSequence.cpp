#include "BattleSequence.h"


enum BattleResults {
    DEFEATED = 0,
    SUCCEEDED = 1,
    TACTICAL_RETREAT = 2
};

struct BattleData {
    BattleResults outcome;
} Battle;

void PlayerAttack()
{

}

void EnemyAttack()
{

}

void PlayerWeaponAttack(Player& player, Enemy& enemy, unsigned int whichWeapon)
{
    // Do damage
    // Check if kills
    // Call loot phase
    switch (whichWeapon) {
        case 0: // Left arm weapon.
            if ((enemy.enemyMech.currentAP_ -= player.playerMech.leftArmWeapon_.WeaponConfigs.AttackPower_) <= 0) {
                enemy.enemyMech.currentAP_ = 0;
            } else {
                enemy.enemyMech.currentAP_ -= player.playerMech.leftArmWeapon_.WeaponConfigs.AttackPower_;
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