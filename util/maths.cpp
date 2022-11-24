#include "Maths.h"

unsigned int getRand() {
    srand((unsigned) time(NULL));
    unsigned int random = rand();
    return random;
}