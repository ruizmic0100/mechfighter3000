#include "GameEventHandler.h"

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
    States state;
    States* nextState;
    States* prevState;
    int Data[1000];
} gamestate;


void GameStart()
{
    gamestate.state = GAME_START;
    std::cout << "Game Start!" << std::endl;
    Start = true; // TODO: Make start menu.

    if (Start) {
        MainMenuPhase();
    }
}

void SpawnEnemy()
{

}

void LoadingPhase()
{
    gamestate.state = LOADING_PHASE;
}

void BattlePhase()
{
    gamestate.state = BATTLE_PHASE;
}

void LootPhase()
{
    gamestate.state = LOOT_PHASE;

}

void MainMenuPhase()
{
    gamestate.state = MAINMENU_PHASE;
    renderer();
}