#include "client_Mortar.h"
#include "WeaponNames.h"

Mortar::Mortar(int ammo): DistanceWeapon(MORTAR_NAME, ammo, false, true) {}

Mortar::~Mortar() {}

Mortar::Mortar(Mortar&& other) : DistanceWeapon(std::move(other)) {}

