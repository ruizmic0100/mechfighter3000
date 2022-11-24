#ifndef GAMEEVENTHANDLER_CLASS_H
#define GAMEEVENTHANDLER_CLASS_H

#include <iostream>
#include <cstdlib>

#include "Player.h"
#include "../graphics/Renderer.h"


inline bool Start;

void GameStart();

void SpawnEnemy();

void LoadingPhase();

void BattlePhase();

void LootPhase();

void MainMenuPhase();



#endif // GAMEEVENTHANDER_CLASS_H