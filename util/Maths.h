#ifndef MATHS_UTILS_H
#define MATHS_UTILS_H

#include <iostream>
#include <cstdlib>
#include <random>

unsigned int getRand();

unsigned int getRandBetween(int Bound);

unsigned int getRandDependingOnRarity(unsigned int Rarity);

unsigned int getRandRarity();

float getRandFloat();

#endif // MATHS_UTILS_H