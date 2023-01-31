#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include <iostream>
#include <vector>
#include <string>

#include "PartsFactory.h"
#include "Mech_Factory.h"

enum EnemyTypes
{
    RUST_CRAB = 0,
    RUST_ENFORCER,
    GRIFFIN
};

class Enemy
{
    public:
        Mech enemyMech;
        std::vector<Part> Loot_;
        std::string Name_;
        unsigned int enemyLevel_;

        Enemy(EnemyTypes enemyType) : enemyLevel_(1) {
            PartsFactory pf;
            
            switch (enemyType) {
                case RUST_CRAB:
                    enemyMech = Mech("Rust Crab", FrameInit(), pf.CreatePart(HEAD,1), pf.CreatePart(CORE,1), pf.CreatePart(ARMS,1), pf.CreatePart(LEGS,1));
                    break;
                case RUST_ENFORCER:
                    enemyMech = Mech("Rust Enforcer", FrameInit(), pf.CreatePart(HEAD,1), pf.CreatePart(CORE,1), pf.CreatePart(ARMS,1), pf.CreatePart(LEGS,1));
                    break;
                case GRIFFIN:
                    enemyMech = Mech("Griffin", FrameInit(), pf.CreatePart(HEAD,1), pf.CreatePart(CORE,1), pf.CreatePart(ARMS,1), pf.CreatePart(LEGS,1));
                    break;
                default:
                    std::cout << "Didn't specify enemy type!" << std::endl;
                    break;
            }


            std::cout << "Enemy Constructed" << std::endl;
        }

};

Enemy EnemyInit(EnemyTypes enemyType);

#endif // ENEMY_CLASS_H