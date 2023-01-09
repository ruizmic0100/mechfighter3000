#ifndef PARTS_FACTORY_H
#define PARTS_FACTORY_H

// TODO: Create a namespace for json object conversion. (https://github.com/nlohmann/json#examples:~:text=To%2partOffsetmake%2partOffsetthis%2partOffsetwork%2partOffsetwith%2partOffsetone%2partOffsetof%2partOffsetyour%2partOffsettypes%2C%2partOffsetyou%2partOffsetonly%2partOffsetneed%2partOffsetto%2partOffsetprovide%2partOffsettwo%2partOffsetfunctions%3A)
// TODO: Move all member function code into cpp file instead of here.
// TODO: Make an exists_ member bool or created_ for the part instances.

#include "../json/json.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

#include "../util/Maths.h"

using json = nlohmann::json;

enum PartType {
    HEAD = 0,
    CORE,
    ARMS,
    LEGS
};

enum Rarity {
    RUST = 0,
    CIVILIAN,
    MILITARY,
    ALIEN
};

// NOTE: Is this still used?
constexpr std::initializer_list<PartType> allPartTypes = {HEAD, CORE, ARMS, LEGS};

typedef struct PartCompleted
{
    PartType Type;
    bool Initialized;
    std::string Name;
    std::string Manufacturer;
    std::string Notes;
    unsigned int PartID;
    unsigned int Price;
    unsigned int Weight;
    unsigned int BallisticDefense;
    unsigned int EnergyDefense;
    unsigned int ArmorPoints;
    unsigned int rarity;

    PartCompleted() : Initialized(false) {}
} Part;

class PartsFactory
{
    public:
        json data_;
        std::vector<Part> MasterPartList_;

        PartsFactory()
        {
            std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
            std::ifstream f(parentDir + "/game/PARTS.json");

            this->data_ = json::parse(f);
        };

        Part GetPart(int PartID) {
        };

        Part CreatePart(PartType typeOfPart, unsigned int partOffset) {
            Part tempPart;
            std::string partNameBase, partNameComplete;

            switch (typeOfPart) {
                case HEAD:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Heads"][partOffset]["Name"].get<std::string>();
                    partNameComplete = partNameBase;
                    tempPart.Name = partNameComplete;

                    // Create a rarity:
                    tempPart.rarity = getRandRarity();

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Heads"][partOffset]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Heads"][partOffset]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Heads"][partOffset]["PartID"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique price:
                    tempPart.Price = this->data_["Heads"][partOffset]["Price"].get<int>();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Heads"][partOffset]["Weight"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Heads"][partOffset]["BallisticDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Heads"][partOffset]["EnergyDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Heads"][partOffset]["ArmorPoints"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    break;
                case CORE:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Core"][partOffset]["Name"].get<std::string>();
                    partNameComplete = partNameBase;
                    tempPart.Name = partNameComplete;

                    // Create a rarity:
                    tempPart.rarity = getRandRarity();

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Core"][partOffset]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Core"][partOffset]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Core"][partOffset]["PartID"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique price:
                    tempPart.Price = this->data_["Core"][partOffset]["Price"].get<int>();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Core"][partOffset]["Weight"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Core"][partOffset]["BallisticDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Core"][partOffset]["EnergyDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Core"][partOffset]["ArmorPoints"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    break;
                case ARMS:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Arms"][partOffset]["Name"].get<std::string>();
                    partNameComplete = partNameBase;
                    tempPart.Name = partNameComplete;

                    // Create a rarity:
                    tempPart.rarity = getRandRarity();

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Arms"][partOffset]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Arms"][partOffset]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Arms"][partOffset]["PartID"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique price:
                    tempPart.Price = this->data_["Arms"][partOffset]["Price"].get<int>();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Arms"][partOffset]["Weight"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Arms"][partOffset]["BallisticDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Arms"][partOffset]["EnergyDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Arms"][partOffset]["ArmorPoints"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    break;
                case LEGS:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Legs"][partOffset]["Name"].get<std::string>();
                    partNameComplete = partNameBase;
                    tempPart.Name = partNameComplete;

                    // Create a rarity:
                    tempPart.rarity = getRandRarity();

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Legs"][partOffset]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Legs"][partOffset]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Legs"][partOffset]["PartID"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique price:
                    tempPart.Price = this->data_["Legs"][partOffset]["Price"].get<int>();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Legs"][partOffset]["Weight"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Legs"][partOffset]["BallisticDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Legs"][partOffset]["EnergyDefense"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Legs"][partOffset]["ArmorPoints"].get<int>() + getRandDependingOnRarity(tempPart.rarity);

                    break;
                default:
                    std::cout << "Did not specify the type of part wanting to be created!" << std::endl;
                    break;
            }

            return tempPart;
        };
};

#endif // PARTS_FACTORY_H