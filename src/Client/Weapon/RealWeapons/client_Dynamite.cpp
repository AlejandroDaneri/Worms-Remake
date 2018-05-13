#include "client_Dynamite.h"
#include "client_Weapons_defs.h"

Dynamite::Dynamite(int ammo): MeleeWeapon(DYNAMITE_NAME, ammo, false, true) {}

Dynamite::~Dynamite() {}

Dynamite::Dynamite(Dynamite&& other) : MeleeWeapon(std::move(other)) {}

