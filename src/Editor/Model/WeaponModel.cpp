
#include "WeaponModel.h"

WeaponModel::WeaponModel(const int &default_ammo)
        : default_ammo(default_ammo),
          actual_ammo(default_ammo) {}

void WeaponModel::resetAmmo() {
    actual_ammo = default_ammo;
}

void WeaponModel::setAmmo(const int &new_ammo) {
    this->actual_ammo = new_ammo;
}

int WeaponModel::getAmmo() const {
    return actual_ammo;
}
