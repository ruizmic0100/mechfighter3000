#include "GameEventHandler.h"
#include "RenderList.h"

GameState gamestate;

int GetGameState()
{
    return gamestate.curr_state;
}

void SetGameState(States gamestateToSetTo)
{
    gamestate.curr_state = gamestateToSetTo;
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
    gamestate.curr_state = LOADING_PHASE;
}

void BattlePhase()
{
    gamestate.curr_state = BATTLE_PHASE;
    // Enemy enemy = SpawnEnemy();
    renderBattleMenu = true;
    BattleState turns;

    std::cout << "Battle Sequence: " << turns.getCurrentState() << std::endl;
}

void LootPhase()
{
    renderBattleMenu = false;
    gamestate.curr_state = LOOT_PHASE;


}

// TODO: Make this actually a main menu with game start - settings - exit game.
void MainMenuPhase()
{
    gamestate.curr_state = MAINMENU_PHASE;
    renderer();
}
