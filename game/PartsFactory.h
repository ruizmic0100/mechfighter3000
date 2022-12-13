#ifndef PARTS_FACTORY_H
#define PARTS_FACTORY_H

// TODO: Create a namespace for json object conversion. (https://github.com/nlohmann/json#examples:~:text=To%20make%20this%20work%20with%20one%20of%20your%20types%2C%20you%20only%20need%20to%20provide%20two%20functions%3A)
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

        Part CreatePart(PartType typeOfPart) {
            Part tempPart;
            std::string partNameBase, partNameComplete;
            unsigned int randomNum = getRand();
            std::string randomNum_str = std::to_string(randomNum);

            switch (typeOfPart) {
                case HEAD:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Heads"][0]["Name"].get<std::string>();
                    partNameComplete = partNameBase + randomNum_str;
                    tempPart.Name = partNameComplete;

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Heads"][0]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Heads"][0]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Heads"][0]["PartID"].get<int>() + getRand();

                    // Create unique price:
                    tempPart.Price = this->data_["Heads"][0]["Price"].get<int>() + getRand();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Heads"][0]["Weight"].get<int>() + getRand();

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Heads"][0]["BallisticDefense"].get<int>() + getRand();

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Heads"][0]["EnergyDefense"].get<int>() + getRand();

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Heads"][0]["ArmorPoints"].get<int>() + getRand();
                    break;
                case CORE:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Core"][0]["Name"].get<std::string>();
                    partNameComplete = partNameBase + randomNum_str;
                    tempPart.Name = partNameComplete;

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Core"][0]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Core"][0]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Core"][0]["PartID"].get<int>() + getRand();

                    // Create unique price:
                    tempPart.Price = this->data_["Core"][0]["Price"].get<int>() + getRand();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Core"][0]["Weight"].get<int>() + getRand();

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Core"][0]["BallisticDefense"].get<int>() + getRand();

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Core"][0]["EnergyDefense"].get<int>() + getRand();

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Core"][0]["ArmorPoints"].get<int>() + getRand();
                    break;
                case ARMS:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Arms"][0]["Name"].get<std::string>();
                    partNameComplete = partNameBase + randomNum_str;
                    tempPart.Name = partNameComplete;

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Arms"][0]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Arms"][0]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Arms"][0]["PartID"].get<int>() + getRand();

                    // Create unique price:
                    tempPart.Price = this->data_["Arms"][0]["Price"].get<int>() + getRand();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Arms"][0]["Weight"].get<int>() + getRand();

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Arms"][0]["BallisticDefense"].get<int>() + getRand();

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Arms"][0]["EnergyDefense"].get<int>() + getRand();

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Arms"][0]["ArmorPoints"].get<int>() + getRand();
                    break;
                case LEGS:
                    std::cout << "Creating Part of type " << typeOfPart << std::endl;
                    tempPart.Type = typeOfPart;

                    // Create unique name:
                    partNameBase = this->data_["Legs"][0]["Name"].get<std::string>();
                    partNameComplete = partNameBase + randomNum_str;
                    tempPart.Name = partNameComplete;

                    // Set Manufacturer:
                    tempPart.Manufacturer = this->data_["Legs"][0]["Manufacturer"];

                    // Set Notes:
                    tempPart.Notes = this->data_["Legs"][0]["Notes"];

                    // Create unique PartID:
                    tempPart.PartID = this->data_["Legs"][0]["PartID"].get<int>() + getRand();

                    // Create unique price:
                    tempPart.Price = this->data_["Legs"][0]["Price"].get<int>() + getRand();

                    // Create unique weight:
                    tempPart.Weight = this->data_["Legs"][0]["Weight"].get<int>() + getRand();

                    // Create unique ballistic defense:
                    tempPart.BallisticDefense = this->data_["Legs"][0]["BallisticDefense"].get<int>() + getRand();

                    // Create unique energy defense:
                    tempPart.EnergyDefense = this->data_["Legs"][0]["EnergyDefense"].get<int>() + getRand();

                    // Create unique armor points:
                    tempPart.ArmorPoints = this->data_["Legs"][0]["ArmorPoints"].get<int>() + getRand();
                    break;
                default:
                    std::cout << "Did not specify the type of part wanting to be created!" << std::endl;
                    break;
            }

            return tempPart;
        };
};

#endif // PARTS_FACTORY_H