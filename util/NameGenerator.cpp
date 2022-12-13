#include "NameGenerator.h"

static const std::vector<std::string> words = 
    {"Accelerator", "Alternator", "Air Vent", "Auto", "Antenna", "Axle", 
    "Battery"};

std::string RandomString()
{
    std::string tempString;
    std::default_random_engine rng( std::time(nullptr) );
    std::uniform_int_distribution<std::size_t> distribution( 0, words.size() - 1 );

    while( tempString.size() < 2 ) tempString += words[ distribution(rng) ];
    return tempString;
}