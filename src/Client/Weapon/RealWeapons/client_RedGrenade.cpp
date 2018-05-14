#include "client_RedGrenade.h"
#include "WeaponNames.h"

RedGrenade::RedGrenade(int ammo): 
	DistanceWeapon(RED_GRENADE_NAME, ammo, true, true) {}

RedGrenade::~RedGrenade() {}

RedGrenade::RedGrenade(RedGrenade&& other) : DistanceWeapon(std::move(other)) {}

