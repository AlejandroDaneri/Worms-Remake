#include "Bat.h"
#include "WeaponNames.h"

Bat::Bat(int ammo): MeleeWeapon(BAT_NAME, ammo, true) {}

Bat::~Bat() {}

Bat::Bat(Bat&& other) : MeleeWeapon(std::move(other)) {}

