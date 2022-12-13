#include "WeaponFactory.h"

WeaponConfigs CreateRandomWeaponConfigs()
{
    wConfigs tempWeaponConfig;

    tempWeaponConfig.Weight_ = getRand();
    tempWeaponConfig.EnergyCost_ = getRand();
    tempWeaponConfig.AttackPower_ = getRand();
    tempWeaponConfig.PhysicalArmorReduction_ = getRand();
    tempWeaponConfig.PhysicalArmorPiercingFactor_ = getRand();
    tempWeaponConfig.ImpactFactor_ = getRand();
    tempWeaponConfig.MeleeAbility_ = getRand();
    tempWeaponConfig.Recoil_ = getRand();
    tempWeaponConfig.AimPrecisions_ = getRand();
    tempWeaponConfig.InitialSpeed_ = getRand();
    tempWeaponConfig.ReloadTime_ = getRand();
    tempWeaponConfig.ReloadTime_ = getRand();
    tempWeaponConfig.NumberOfMagazines_ = getRand();
    tempWeaponConfig.MagazineCapacity_ = getRand();
    tempWeaponConfig.SimultaneousFireCount_ = getRand();
    tempWeaponConfig.EnergyChargeRequired_ = getRand();
    tempWeaponConfig.Price_ = getRand();

    return tempWeaponConfig;
}