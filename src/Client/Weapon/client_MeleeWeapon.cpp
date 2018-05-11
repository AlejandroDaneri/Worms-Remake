#include "client_MeleeWeapon.h"
#include <limits>

MeleeWeapon::MeleeWeapon(std::string name, int ammo, int damage, int radius, bool scope, bool timed) :
	Weapon(name, ammo, damage, radius) {
	this->has_Scope = scope;
	this->is_Timed = timed;
}

void MeleeWeapon::changeTime(int time) {}

