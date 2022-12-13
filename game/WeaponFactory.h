#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <iostream>
#include <vector>
#include <string>

#include "../util/Maths.h"
#include "../util/enumFactory.h"
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
    unsigned int AimPrecisions_; // Initial accuracy of the weapon.
    unsigned int InitialSpeed_; // Which weapon is faster.
    unsigned int ReloadTime_; // How long in seconds it takes to reload the weapon.
    unsigned int NumberOfMagazines_; // How much reserved ammo for the weapon.
    unsigned int MagazineCapacity_; // How much ammo per reload.
    unsigned int SimultaneousFireCount_; // What the ammo expendeture is per action.
    unsigned int EnergyChargeRequired_; // How much energy the weapon needs to shoot incase it's a big chonker type y'kn0w?
    unsigned int Price_; // How much it is worth.
} wConfigs;

typedef struct Weapon
{
    WeaponType WType;
    wConfigs WeaponConfigs;
    std::string Name;
    std::string Manufacturer;
    std::string Notes;
    unsigned int weaponPartID;
};


class WeaponFactory
{
    public:
        std::vector<Weapon> Weapons;

        // Empty Constructor for ease of use.
        WeaponFactory() {
            
        }

        Weapon CreateWeapon(WeaponType wType, wConfigs WeaponConfigs, std::string Name, std::string Manufacturer, std::string Notes) {
            Weapon weaponBP;

            weaponBP.Name = Name;
            weaponBP.Manufacturer = Manufacturer;
            weaponBP.Notes = Notes;
            weaponBP.weaponPartID = getRand();

            weaponBP.WType = wType;

            weaponBP.WeaponConfigs = WeaponConfigs;
            std::cout << "Created weapon of " << wType << " type." << std::endl;
            return weaponBP;
        }
};


WeaponConfigs CreateRandomWeaponConfigs();

#endif // WEAPON_FACTORY_H