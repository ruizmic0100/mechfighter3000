#include "NameGenerator.h"

static const std::vector<std::string> words = 
    {"Accelerator", "Alternator", "Air Vent", "Auto", "Antenna", "Axle", 
    "Battery", "Camshaft", "Console", "Cylinder", "Defroster", "Differential",
    "Block", "Engine", "Ignition", "Manifold", "Radiator", "Absorber",
    "Charger"};

std::default_random_engine rng( std::time(nullptr) );

std::string RandomString()
{
    std::string tempString;
    std::uniform_int_distribution<std::size_t> distribution( 0, words.size() - 1 );

    while( tempString.size() < 2 ) tempString += words[ distribution(rng) ];
    return tempString;
}