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
    srand((unsigned) time(NULL));
    gamestate.state = GAME_START;
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
    gamestate.state = LOADING_PHASE;
}

void BattlePhase()
{
    gamestate.state = BATTLE_PHASE;
    // Enemy enemy = SpawnEnemy();

    // TODO: Find a better way to hold these bools.
    // NOTE: Might be good that I am doing this after everything is setup.
    RenderEnemyMenu = true;

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