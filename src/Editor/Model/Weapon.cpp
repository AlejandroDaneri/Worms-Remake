
#include "Weapon.h"

Weapon::Weapon(const int &default_ammo)
        : default_ammo(default_ammo),
          actual_ammo(default_ammo) {}

void Weapon::resetAmmo() {
    actual_ammo = default_ammo;
}

void Weapon::setAmmo(const int &new_ammo) {
    this->actual_ammo = new_ammo;
}

int Weapon::getAmmo() const {
    return actual_ammo;
}
