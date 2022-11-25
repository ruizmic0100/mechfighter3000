#ifndef PARTS_FACTORY_H
#define PARTS_FACTORY_H

// TODO: Create a namespace for json object conversion. (https://github.com/nlohmann/json#examples:~:text=To%20make%20this%20work%20with%20one%20of%20your%20types%2C%20you%20only%20need%20to%20provide%20two%20functions%3A)

#include "../json/json.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>

#include "../util/Maths.h"

using json = nlohmann::json;

typedef struct
{
    std::string Name;
    std::string Manufacturer;
    std::string Notes;
    unsigned int PartID;
    unsigned int Price;
    unsigned int Weight;
    unsigned int BallisticDefense;
    unsigned int EnergyDefense;
    unsigned int ArmorPoints;
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

        Part CreatePart() {
            Part tempPart;
            unsigned int randomNum = getRand();
            std::string randomNum_str = std::to_string(randomNum);

            // Create unique name:
            std::string partNameBase = this->data_["Heads"][0]["Name"].get<std::string>();
            std::string partNameComplete = partNameBase + randomNum_str;
            tempPart.Name = partNameComplete;

            // Set Manufacturer:
            tempPart.Manufacturer = this->data_["Heads"][0]["Manufacturer"];

            // Set Notes:
            tempPart.Notes = this->data_["Heads"][0]["Notes"];

            // Create unique PartID:
            tempPart.PartID = this->data_["Heads"][0]["PartID"].get<int>() + randomNum;

            // Create unique price:
            tempPart.Price = (randomNum * getRand()) / 1000;

            // Create unique weight:
            tempPart.Weight = (randomNum * getRand()) / 10000;

            // Create unique ballistic defense:
            tempPart.BallisticDefense = (randomNum * getRand()) / 10000;

            // Create unique energy defense:
            tempPart.EnergyDefense = (randomNum * getRand()) / 10000;

            // Create unique armor points:
            tempPart.ArmorPoints = (randomNum * getRand()) / 10000;

            return tempPart;
        };
};

#endif // PARTS_FACTORY_H