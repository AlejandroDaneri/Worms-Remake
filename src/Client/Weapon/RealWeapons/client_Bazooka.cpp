#include "client_Bazooka.h"
#include "client_Weapons_defs.h"

Bazooka::Bazooka(int ammo) : DistanceWeapon(BAZOOKA_NAME, ammo) {}

Bazooka::~Bazooka(){}

Bazooka::Bazooka(Bazooka&& other) : DistanceWeapon(std::move(other)) {}

