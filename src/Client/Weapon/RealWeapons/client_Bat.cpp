#include "client_Bat.h"
#include "client_Weapons_defs.h"

Bat::Bat(int ammo): MeleeWeapon(BAT_NAME, ammo, true) {}

Bat::~Bat() {}

Bat::Bat(Bat&& other) : MeleeWeapon(std::move(other)) {}

