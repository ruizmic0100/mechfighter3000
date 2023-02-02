#ifndef GAMEEVENTHANDLER_CLASS_H
#define GAMEEVENTHANDLER_CLASS_H

#include <iostream>
#include <cstdlib>

#include "renderer.h"
#include "Player.h"
#include "Enemy.h"
#include "BattleSequence.h"

enum States
{
    GAME_START = 0,
    MAINMENU_PHASE,
    BATTLE_PHASE,
    LOOT_PHASE,
    LOADING_PHASE,
    GAME_END
};

struct GameState
{
    States curr_state;
    States* next_state;
    States* prev_state;
    int Data[1000];
};


inline bool Start;

int GetGameState();

void SetGameState();

void DeliverExperience(Player& player, Enemy& enemy);

void GameStart();

Enemy SpawnEnemy();

void LoadingPhase();

void BattlePhase();

void LootPhase(Player& player, Enemy& enemy);

void MainMenuPhase();

void PlayerWeaponAttack(Player& player, Enemy& enemy, unsigned int whichWeapon);


#endif // GAMEEVENTHANDER_CLASS_H