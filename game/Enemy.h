#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include <iostream>
#include <vector>
#include <string>

#include "PartsFactory.h"

class Enemy
{
    public:
        std::vector<Part> Loot_;
        std::string Name_;
        int Level;

        Enemy() {
            std::cout << "Enemy Constructed" << std::endl;
        }

};

#endif // ENEMY_CLASS_H