#include "Dynamite.h"
#include "WeaponNames.h"

Dynamite::Dynamite(int ammo): MeleeWeapon(DYNAMITE_NAME, ammo, false, true) {}

Dynamite::~Dynamite() {}

Dynamite::Dynamite(Dynamite&& other) : MeleeWeapon(std::move(other)) {}

