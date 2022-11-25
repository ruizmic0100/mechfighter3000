#ifndef GAMEEVENTHANDLER_CLASS_H
#define GAMEEVENTHANDLER_CLASS_H

#include <iostream>
#include <cstdlib>

#include "Player.h"
#include "Enemy.h"
#include "../graphics/Renderer.h"


inline bool Start;

void GameStart();

Enemy SpawnEnemy();

void LoadingPhase();

void BattlePhase();

void LootPhase();

void MainMenuPhase();



#endif // GAMEEVENTHANDER_CLASS_H