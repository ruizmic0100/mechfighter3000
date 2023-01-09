#include "Maths.h"

unsigned int getRand()
{
    unsigned int random = rand();
    return random;
}

unsigned int getRandBetween(int Bound)
{
    unsigned int random = rand() % Bound;
    return random;
}

unsigned int getRandDependingOnRarity(unsigned int Rarity)
{
    switch (Rarity) {
        case 0:
            return getRandBetween(10);
            break;
        case 1:
            return getRandBetween(100);
            break;
        case 2:
            return getRandBetween(500);
            break;
        case 3:
            return getRandBetween(1000);
            break;
        default:
            std::cout << "Could not interpret rarity to get random num depending on rarity" << std::endl;
            break;
    }

    return 1;
}

unsigned int getRandRarity()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({50, 30, 19, 1});
    unsigned int rarity = d(gen);

    return rarity;
}

float getRandFloat()
{
    float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return random;
}