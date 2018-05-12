#include "client_Mortar.h"
#include "client_Weapons_defs.h"

Mortar::Mortar(int ammo): DistanceWeapon(MORTAR_NAME, ammo, false, true) {}

Mortar::~Mortar() {}

