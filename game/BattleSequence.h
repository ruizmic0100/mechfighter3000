#ifndef BATTLE_SEQUENCE_H
#define BATTLE_SEQUENCE_H

#include "Player.h"
#include "Enemy.h"


enum BATTLESTATES
{
    PLAYER=0,
    ENEMY=1
};


class BattleState
{
    public:
        BATTLESTATES State_, prevState_, nextState_;

        BattleState() : State_(PLAYER) {
        }

        void setCurrentState(BATTLESTATES battleState) {
            this->State_ = battleState;
        }

        int getCurrentState() {
            return this->State_;
        }

};

#endif // BATTLE_SEQUENCE_H