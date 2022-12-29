#include "Maths.h"

unsigned int getRand()
{
    unsigned int random = rand();
    return random;
}

float getRandFloat()
{
    float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return random;
}