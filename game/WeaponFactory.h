#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "../json/json.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

#include "../util/Maths.h"
#include "../util/enumFactory.h"

using json = nlohmann::json;

#define WEAPONTYPE(XX) \
    XX(HANDGUN, =0) \
    XX(RIFLE, =1) \
    XX(MACHINE_GUN, =2) \
    XX(SNIPER_RIFLE, =3) \
    XX(PLASMA_CANNON, =4) \

// enum WeaponType
// {
//     HANDGUN = 0,
//     RIFLE,
//     MACHINE_GUN,
//     SNIPER_RIFLE,
//     BAZOOKA,
//     FLAMETHROWER,
//     PULSE_RIFLE,
//     LASER_RIFLE,
//     LASER_BLADE,
//     MISSILE,
//     ROCKET,
//     CHAIN_GUN,
//     SLUG_GUN,
//     GRENADE_LAUNCHER,
//     PULSE_CANNON,
//     LASER_CANNON,
//     PLASMA_CANNON,
// };

DECLARE_ENUM(WeaponType, WEAPONTYPE)


constexpr std::initializer_list<WeaponType> testWeaponTypes = {HANDGUN, RIFLE, MACHINE_GUN, SNIPER_RIFLE, PLASMA_CANNON};

typedef struct WeaponConfigs
{
    unsigned int Weight_; // Weight of the weapon.
    unsigned int EnergyCost_; // What it costs to use the weapon per action.
    unsigned int AttackPower_; // Baseline damage.
    unsigned int PhysicalArmorReduction_; // Do more damage over time with armor breaking weapons.
    unsigned int PhysicalArmorPiercingFactor_; // Sniper rifles can skip the armor breaking stage and just do flat damage.
    unsigned int ImpactFactor_; // Higher impact means the quicker their stun bar builds.
    unsigned int MeleeAbility_; // How much damage when used as a melee weapon.
    unsigned int Recoil_; // How hard it is to take precise repeated shots with the weapon.
    unsigned int AimPrecisions_; // Initial accuracy of the weapon. (%)
    unsigned int InitialSpeed_; // Which weapon is faster. (ms)
    unsigned int ReloadTime_; // How long in seconds it takes to reload the weapon. (ms)
    unsigned int NumberOfMagazines_; // How much reserved ammo for the weapon.
    unsigned int MagazineCapacity_; // How much ammo per reload.
    unsigned int SimultaneousFireCount_; // What the ammo expendeture is per action.
    unsigned int EnergyChargeRequired_; // How much energy the weapon needs to shoot incase it's a big chonker type y'kn0w?
    unsigned int Price_; // How much it is worth.
} wConfigs;

typedef struct WeaponCompleted
{
    bool Initialized;
    bool Equipped;
    WeaponType WType;
    int slotCompatability; // 0: arms, 1: shoulders.
    wConfigs WeaponConfigs;
    std::string Name;
    std::string Manufacturer;
    std::string Notes;
    unsigned int rarity;
    unsigned int weaponPartID;

    WeaponCompleted() : Initialized(false), Equipped(false) {}
} Weapon;


class WeaponFactory
{
    public:
        json data_;
        std::vector<Weapon> Weapons;

        // Empty Constructor for ease of use.
        WeaponFactory() {
            std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
            std::ifstream f(parentDir + "/game/WEAPONS.json");

            this->data_ = json::parse(f);
        }

        Weapon CreateWeapon(WeaponType wType, unsigned int weaponOffset) {
            Weapon weaponBP;

            switch (wType) {
                case HANDGUN:
                    weaponBP.rarity = getRandRarity();
                    weaponBP.slotCompatability = 0;

                    weaponBP.Name = this->data_["Handgun"][weaponOffset]["Name"].get<std::string>();
                    weaponBP.Manufacturer = this->data_["Handgun"][weaponOffset]["Manufacturer"].get<std::string>();
                    weaponBP.WType = wType;
                    weaponBP.Notes = this->data_["Handgun"][weaponOffset]["Notes"].get<std::string>();
                    weaponBP.weaponPartID = this->data_["Handgun"][weaponOffset]["WeaponID"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.Price_ = this->data_["Handgun"][weaponOffset]["Price"].get<int>();
                    weaponBP.WeaponConfigs.Weight_ = this->data_["Handgun"][weaponOffset]["Weight"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.EnergyCost_ = this->data_["Handgun"][weaponOffset]["EnergyCost"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.AttackPower_ = this->data_["Handgun"][weaponOffset]["AttackPower"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.PhysicalArmorReduction_ = this->data_["Handgun"][weaponOffset]["PhysicalArmorReduction"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.PhysicalArmorPiercingFactor_ = this->data_["Handgun"][weaponOffset]["PhysicalArmorPiercingFactor"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.ImpactFactor_ = this->data_["Handgun"][weaponOffset]["ImpactFactor"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.MeleeAbility_ = this->data_["Handgun"][weaponOffset]["MeleeAbility"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.Recoil_ = this->data_["Handgun"][weaponOffset]["Recoil"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.AimPrecisions_ = this->data_["Handgun"][weaponOffset]["AimPrecisions"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.InitialSpeed_ = this->data_["Handgun"][weaponOffset]["InitialSpeed"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.ReloadTime_ = this->data_["Handgun"][weaponOffset]["ReloadTime"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.NumberOfMagazines_ = this->data_["Handgun"][weaponOffset]["NumberOfMagazines"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.SimultaneousFireCount_ = this->data_["Handgun"][weaponOffset]["SimultaneousFireCount"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);
                    weaponBP.WeaponConfigs.EnergyChargeRequired_ = this->data_["Handgun"][weaponOffset]["EnergyChargeRequired"].get<int>() + getRandDependingOnRarity(weaponBP.rarity);

                    std::cout << "Created weapon of " << wType << " type " << "With weaponPartID: " << weaponBP.weaponPartID << std::endl;
                    break;
                default:
                    std::cout << "Could not interpret wType when creating weapon" << std::endl;
                    break;
            }
            return weaponBP;
        }
};


WeaponConfigs CreateRandomWeaponConfigs();

#endif // WEAPON_FACTORY_H